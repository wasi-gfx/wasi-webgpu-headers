#include "async_futures.h"

#include <stdlib.h>
#include <string.h>

// Canonical component-model built-ins, re-declared so this module stands alone.

__attribute__((__import_module__("$root"), __import_name__("[subtask-drop]")))
extern void __af_subtask_drop(uint32_t handle);

__attribute__((__import_module__("$root"), __import_name__("[waitable-set-new]")))
extern uint32_t __af_waitable_set_new(void);

__attribute__((__import_module__("$root"), __import_name__("[waitable-join]")))
extern void __af_waitable_join(uint32_t waitable, uint32_t set);

__attribute__((__import_module__("$root"), __import_name__("[waitable-set-wait]")))
extern uint32_t __af_waitable_set_wait(uint32_t set, uint32_t* payload);

__attribute__((__import_module__("$root"), __import_name__("[waitable-set-poll]")))
extern uint32_t __af_waitable_set_poll(uint32_t set, uint32_t* payload);

// waitable-set.wait / .poll return the event kind and write [waitable, code]
// into the payload buffer. We only care about subtask-completion events.
#define AF_EVENT_NONE 0
#define AF_EVENT_SUBTASK 1

// an async_call_desc after registration.
// the trailing fields mirror it, but args_copy and result are blocks this module owns and frees after dispatch
typedef struct future_entry {
    // handed back to the caller
    async_future_t id;
    // valid iff `running`
    uint32_t subtask;
    // subtask live and joined to the set
    bool running;

    void* args_copy;
    void (*args_free)(void* args);
    void* result;
    void (*on_done)(void* result, void* userdata);
    void* userdata;
    uint32_t tag;
} future_entry;

static future_entry** g_pending = NULL;
static size_t g_pending_len = 0;
static size_t g_pending_cap = 0;
static async_future_t g_next_id = 1;
static uint32_t g_set = 0;
static bool g_set_init = false;

static uint32_t waitable_set(void) {
    if (!g_set_init) {
        g_set = __af_waitable_set_new();
        g_set_init = true;
    }
    return g_set;
}

static future_entry* register_entry(uint32_t status) {
    future_entry* f = malloc(sizeof(future_entry));
    if (!f) abort();
    *f = (future_entry){.id = g_next_id++};
    switch (ASYNC_SUBTASK_STATE(status)) {
    case ASYNC_SUBTASK_STARTING:
    case ASYNC_SUBTASK_STARTED:
        f->running = true;
        f->subtask = ASYNC_SUBTASK_HANDLE(status);
        __af_waitable_join(f->subtask, waitable_set());
        break;
    case ASYNC_SUBTASK_RETURNED:
        // completed synchronously, ready to dispatch
        f->running = false;
        break;
    case ASYNC_SUBTASK_STARTED_CANCELLED:
    case ASYNC_SUBTASK_RETURNED_CANCELLED:
        // TODO: support canceling
        abort();
    default:
        // should be unreachable
        abort();
    }
    if (g_pending_len == g_pending_cap) {
        size_t cap = g_pending_cap ? g_pending_cap * 2 : 8;
        future_entry** pending = realloc(g_pending, cap * sizeof(*g_pending));
        if (!pending) abort();
        g_pending = pending;
        g_pending_cap = cap;
    }
    g_pending[g_pending_len++] = f;
    return f;
}

async_future_t async_call(async_call_desc desc) {
    void* args_copy = NULL;
    if (desc.args_size > 0) {
        if (!desc.args) abort();
        args_copy = malloc(desc.args_size);
        if (!args_copy) abort();
        memcpy(args_copy, desc.args, desc.args_size);
    }
    void* result = NULL;
    if (desc.result_size > 0) {
        result = malloc(desc.result_size);
        if (!result) abort();
    }
    uint32_t status = desc.call(args_copy, result);
    future_entry* f = register_entry(status);
    f->on_done = desc.on_done;
    f->userdata = desc.userdata;
    f->tag = desc.tag;
    f->args_copy = args_copy;
    f->args_free = desc.args_free;
    f->result = result;
    return f->id;
}

bool async_future_pending(async_future_t id) {
    for (size_t i = 0; i < g_pending_len; i++) {
        if (g_pending[i]->id == id) return true;
    }
    return false;
}

bool async_future_issued(async_future_t id) {
    return id != 0 && id < g_next_id;
}

size_t async_pending_count(void) {
    return g_pending_len;
}

static bool any_running(void) {
    for (size_t i = 0; i < g_pending_len; i++) {
        if (g_pending[i]->running) return true;
    }
    return false;
}

static void mark_returned(uint32_t waitable) {
    for (size_t i = 0; i < g_pending_len; i++) {
        if (g_pending[i]->running && g_pending[i]->subtask == waitable) {
            // remove from the set
            __af_waitable_join(g_pending[i]->subtask, 0);
            __af_subtask_drop(g_pending[i]->subtask);
            g_pending[i]->running = false;
            return;
        }
    }
}

static void handle_event(uint32_t kind, uint32_t const payload[2]) {
    if (kind != AF_EVENT_SUBTASK) return;
    switch (ASYNC_SUBTASK_STATE(payload[1])) {
    case ASYNC_SUBTASK_STARTING:
    case ASYNC_SUBTASK_STARTED:
        // still running, wait for a later event
        break;
    case ASYNC_SUBTASK_RETURNED:
        mark_returned(payload[0]);
        break;
    case ASYNC_SUBTASK_STARTED_CANCELLED:
    case ASYNC_SUBTASK_RETURNED_CANCELLED:
        // TODO: support canceling
        abort();
    default:
        // should be unreachable
        abort();
    }
}

static void complete_at(size_t i) {
    // Remove before the callback runs since the callback may re-enter.
    future_entry* f = g_pending[i];
    g_pending[i] = g_pending[g_pending_len - 1];
    g_pending_len--;
    if (f->on_done) f->on_done(f->result, f->userdata);
    if (f->args_free && f->args_copy) f->args_free(f->args_copy);
    free(f->args_copy);
    free(f->result);
    free(f->userdata);
    free(f);
}

// Dispatches every ready future.
// `may`: decides which may fire now (NULL accepts all)
// `block`: wait on the waitable set when nothing is dispatchable yet.
// Futures `may` rejects stay registered for a later drain.
static size_t drain(bool block, async_may_dispatch_t may, void* ctx) {
    size_t dispatched = 0;
    for (;;) {
        while (any_running()) {
            // [waitable, code]
            uint32_t payload[2] = {0, 0};
            uint32_t kind = __af_waitable_set_poll(waitable_set(), payload);
            if (kind == AF_EVENT_NONE) break;
            handle_event(kind, payload);
        }

        // Rescan after each dispatch: a re-entrant callback may reorder entries.
        bool progressed = false;
        bool rescan = true;
        while (rescan) {
            rescan = false;
            for (size_t i = 0; i < g_pending_len; i++) {
                future_entry* f = g_pending[i];
                if (!f->running && (may == NULL || may(f->id, f->tag, ctx))) {
                    complete_at(i);
                    dispatched++;
                    progressed = true;
                    rescan = true;
                    break;
                }
            }
        }

        if (block && !progressed && any_running()) {
            // [waitable, code]
            uint32_t payload[2] = {0, 0};
            uint32_t kind = __af_waitable_set_wait(waitable_set(), payload);
            handle_event(kind, payload);
            continue;
        }
        return dispatched;
    }
}

void async_dispatch_ready(async_may_dispatch_t may, void* ctx) {
    drain(false, may, ctx);
}

bool async_block_on_any(async_may_dispatch_t may, void* ctx) {
    return drain(true, may, ctx) > 0;
}

void async_block_on(async_future_t id) {
    while (async_future_pending(id)) {
        // no live subtask can make progress
        if (!async_block_on_any(NULL, NULL)) return;
    }
}

void async_block_on_all(void) {
    while (g_pending_len > 0) {
        if (!async_block_on_any(NULL, NULL)) {
            // synchronously-ready leftovers
            async_dispatch_ready(NULL, NULL);
            return;
        }
    }
}
