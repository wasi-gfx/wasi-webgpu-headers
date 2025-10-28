// WIP hello compute example

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

bool exports_wasi_cli_run_run() {
    instance = wgpuCreateInstance(NULL);

    WGPURequestAdapterCallbackInfo adapter_callback_info = {
        .nextInChain = NULL,
        .callback = &adapter_callback,
        .userdata1 = NULL,
        .userdata2 = NULL
    };
    wgpuInstanceRequestAdapter(
        instance,
        NULL,
        adapter_callback_info
    );
    
    WGPURequestDeviceCallbackInfo device_callback_info = {
        .nextInChain = NULL,
        .callback = &device_callback,
        .userdata1 = NULL,
        .userdata2 = NULL
    };
    wgpuAdapterRequestDevice(
        adapter,
        NULL,
        device_callback_info
    );

    return true;
}
