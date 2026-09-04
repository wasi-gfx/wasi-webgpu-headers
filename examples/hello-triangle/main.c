// WIP hello triangle example

#include "../../webgpu.c"
#include "../command.h"

WGPUInstance instance;
WGPUAdapter adapter;
WGPUDevice device;
WGPUQueue queue;

void device_callback(WGPURequestDeviceStatus status, WGPUDevice created_device, WGPUStringView message, void* userdata1, void* userdata2)
{
    device = created_device;
}

void adapter_callback(WGPURequestAdapterStatus status, WGPUAdapter created_adapter, WGPUStringView message, void* userdata1, void* userdata2)
{
    adapter = created_adapter;
}

// `run` is lifted synchronously (see the Makefile's --async filter), so it may
// block. wgpuInstanceWaitAny drives the async webgpu imports to completion.
bool exports_wasi_cli_run_run() {
    instance = wgpuCreateInstance(NULL);

    WGPURequestAdapterCallbackInfo adapter_callback_info = {
        .nextInChain = NULL,
        .mode = WGPUCallbackMode_WaitAnyOnly,
        .callback = &adapter_callback,
        .userdata1 = NULL,
        .userdata2 = NULL
    };
    WGPUFuture adapter_future = wgpuInstanceRequestAdapter(
        instance,
        NULL,
        adapter_callback_info
    );
    wgpuInstanceWaitAny(instance, 1, &(WGPUFutureWaitInfo){.future = adapter_future}, UINT64_MAX);

    WGPURequestDeviceCallbackInfo device_callback_info = {
        .nextInChain = NULL,
        .mode = WGPUCallbackMode_WaitAnyOnly,
        .callback = &device_callback,
        .userdata1 = NULL,
        .userdata2 = NULL
    };
    WGPUFuture device_future = wgpuAdapterRequestDevice(
        adapter,
        NULL,
        device_callback_info
    );
    wgpuInstanceWaitAny(instance, 1, &(WGPUFutureWaitInfo){.future = device_future}, UINT64_MAX);

    return true;
}
