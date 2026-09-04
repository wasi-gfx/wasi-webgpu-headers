// Drives wit-bindgen `async func` imports to completion from synchronous C.
//
// Such an import returns instead of blocking, handing back a status word. It
// either already RETURNED, meaning the result block is written, or it STARTED
// and carries a subtask handle to wait on. This module tracks the started ones
// and fires a callback when each finishes.
//
// Single threaded, and depends on nothing but libc.
// The blocking calls wait on the component-model waitable-set.

#ifndef ASYNC_FUTURES_H
#define ASYNC_FUTURES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// identifies a registered operation, handed out from 1
typedef uint64_t async_future_t;

// decodes the subtask-status a wit-bindgen `[async-lower]` import returns
#define ASYNC_SUBTASK_STATE(status)  ((uint32_t)((status) & 0xf))
#define ASYNC_SUBTASK_HANDLE(status) ((uint32_t)((status) >> 4))
enum {
    ASYNC_SUBTASK_STARTING,
    ASYNC_SUBTASK_STARTED,
    ASYNC_SUBTASK_RETURNED,
    ASYNC_SUBTASK_STARTED_CANCELLED,
    ASYNC_SUBTASK_RETURNED_CANCELLED,
};

typedef struct {
    // invokes the generated import
    uint32_t (*call)(void* args, void* result);
    // copied before the call, may be NULL
    void const* args;
    size_t args_size;
    // frees heap data inside the args copy, may be NULL
    void (*args_free)(void* args);
    size_t result_size;
    void (*on_done)(void* result, void* userdata);
    // context for on_done, one malloc'd block, freed after it runs
    void* userdata;
    // context for async_may_dispatch_t, which has no way to read userdata
    uint32_t tag;
} async_call_desc;

async_future_t async_call(async_call_desc desc);

// true until the operation completes and its callback has run
bool async_future_pending(async_future_t id);

// true if this id was ever handed out
bool async_future_issued(async_future_t id);

// how many operations are still registered
size_t async_pending_count(void);

// decides whether a completed operation may fire its callback right now
typedef bool (*async_may_dispatch_t)(async_future_t id, uint32_t tag, void* ctx);

// fires callbacks for completed operations `may` accepts (NULL accepts all), without blocking
void async_dispatch_ready(async_may_dispatch_t may, void* ctx);

// fires callbacks for completed operations `may` accepts (NULL accepts all), blocking
// returns false if nothing was running to wait for, to avoid spinning
bool async_block_on_any(async_may_dispatch_t may, void* ctx);

// blocks until `id` has completed and its callback has run
void async_block_on(async_future_t id);

// blocks until every registered operation has completed
void async_block_on_all(void);

// TODO: support cancelation

#endif // ASYNC_FUTURES_H
