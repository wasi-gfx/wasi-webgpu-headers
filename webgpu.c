#include "webgpu/webgpu.h"

#include <stdlib.h>
#include <string.h>
#include <stdnoreturn.h>

#include "imports.h"

noreturn void todo()
{
    abort();
}

noreturn void unreachable()
{
    abort();
}

typedef struct WGPUAdapterImpl {
    wasi_webgpu_webgpu_own_gpu_adapter_t adapter;
    uint32_t refCount;
} WGPUAdapterImpl;
// typedef struct WGPUBindGroupImpl {
// } WGPUBindGroupImpl;
// typedef struct WGPUBindGroupLayoutImpl {
// } WGPUBindGroupLayoutImpl;
// typedef struct WGPUBufferImpl {
// } WGPUBufferImpl;
// typedef struct WGPUCommandBufferImpl {
// } WGPUCommandBufferImpl;
// typedef struct WGPUCommandEncoderImpl {
// } WGPUCommandEncoderImpl;
// typedef struct WGPUComputePassEncoderImpl {
// } WGPUComputePassEncoderImpl;
// typedef struct WGPUComputePipelineImpl {
// } WGPUComputePipelineImpl;
typedef struct WGPUDeviceImpl {
    wasi_webgpu_webgpu_own_gpu_device_t device;
    uint32_t refCount;
} WGPUDeviceImpl;
typedef struct WGPUInstanceImpl {
    wasi_webgpu_webgpu_own_gpu_t gpu;
    uint32_t refCount;
} WGPUInstanceImpl;
// typedef struct WGPUPipelineLayoutImpl {
// } WGPUPipelineLayoutImpl;
// typedef struct WGPUQuerySetImpl {
// } WGPUQuerySetImpl;
// typedef struct WGPUQueueImpl {
// } WGPUQueueImpl;
// typedef struct WGPURenderBundleImpl {
// } WGPURenderBundleImpl;
// typedef struct WGPURenderBundleEncoderImpl {
// } WGPURenderBundleEncoderImpl;
// typedef struct WGPURenderPassEncoderImpl {
// } WGPURenderPassEncoderImpl;
// typedef struct WGPURenderPipelineImpl {
// } WGPURenderPipelineImpl;
// typedef struct WGPUSamplerImpl {
// } WGPUSamplerImpl;
// typedef struct WGPUShaderModuleImpl {
// } WGPUShaderModuleImpl;
// typedef struct WGPUSurfaceImpl {
// } WGPUSurfaceImpl;
// typedef struct WGPUTextureImpl {
// } WGPUTextureImpl;
// typedef struct WGPUTextureViewImpl {
// } WGPUTextureViewImpl;

imports_option_string_t featureLevelNativeToWasi(WGPUFeatureLevel featureLevel);
wasi_webgpu_webgpu_option_gpu_power_preference_t powerPreferenceNativeToWasi(WGPUPowerPreference powerPreference);
wasi_webgpu_webgpu_gpu_feature_name_t featureNativeToWasi(WGPUFeatureName const feature);
WGPUFeatureName featureWasiToNative(wasi_webgpu_webgpu_gpu_feature_name_t const feature);
wasi_webgpu_webgpu_option_own_record_option_gpu_size64_t limitsNativeToWasi(WGPULimits const* limits_native);

WGPUInstance wgpuCreateInstance(WGPUInstanceDescriptor const* descriptor)
{
    WGPUInstanceImpl* instance = malloc(sizeof(WGPUInstanceImpl));
    instance->refCount = 1;
    instance->gpu = wasi_webgpu_webgpu_get_gpu();
    return instance;
}

// WGPUStatus wgpuGetInstanceCapabilities(WGPUInstanceCapabilities* capabilities)
// {
// }

// WGPUProc wgpuGetProcAddress(WGPUStringView procName)
// {
// }

// void wgpuAdapterGetFeatures(WGPUAdapter adapter, WGPUSupportedFeatures* features)
// {
// }

// WGPUStatus wgpuAdapterGetInfo(WGPUAdapter adapter, WGPUAdapterInfo* info)
// {
// }

// WGPUStatus wgpuAdapterGetLimits(WGPUAdapter adapter, WGPULimits* limits)
// {
// }

// WGPUBool wgpuAdapterHasFeature(WGPUAdapter adapter, WGPUFeatureName feature)
// {
// }

WGPUFuture wgpuAdapterRequestDevice(WGPUAdapter adapter, WGPUDeviceDescriptor const* descriptor, WGPURequestDeviceCallbackInfo callbackInfo)
{
    if(!adapter) unreachable();

    wasi_webgpu_webgpu_gpu_device_descriptor_t descriptor_wasi = {};

    if (descriptor)
    {
        descriptor_wasi.required_limits = limitsNativeToWasi(descriptor->requiredLimits);

        if (descriptor->requiredFeatures)
        {
            descriptor_wasi.required_features.is_some = true;
            descriptor_wasi.required_features.val = (wasi_webgpu_webgpu_list_gpu_feature_name_t){
                .ptr = malloc(descriptor->requiredFeatureCount * sizeof(wasi_webgpu_webgpu_gpu_feature_name_t)),
                .len = descriptor->requiredFeatureCount,
            };
            
            for (size_t i = 0; i < descriptor->requiredFeatureCount; i++)
            {
                descriptor_wasi.required_features.val.ptr[i] = featureNativeToWasi(descriptor->requiredFeatures[i]);
            }
        }
    }

    wasi_webgpu_webgpu_own_gpu_device_t wasi_device;
    wasi_webgpu_webgpu_request_device_error_t err;
    bool success = wasi_webgpu_webgpu_method_gpu_adapter_request_device(
        wasi_webgpu_webgpu_borrow_gpu_adapter(adapter->adapter),
        descriptor ? &descriptor_wasi : NULL,
        &wasi_device,
        &err
    );

    if (!success)
    {
        wasi_webgpu_webgpu_request_device_error_free(&err);
        todo();
    }

    WGPUDeviceImpl * device = malloc(sizeof(WGPUDeviceImpl));
    device->refCount = 1;
    device->device = wasi_device;

    wasi_webgpu_webgpu_gpu_device_descriptor_free(&descriptor_wasi);

    callbackInfo.callback(WGPURequestDeviceStatus_Success, device, WGPU_STRING_VIEW_INIT, callbackInfo.userdata1, callbackInfo.userdata2);
    return (WGPUFuture) { .id = -1 };
}

void wgpuAdapterAddRef(WGPUAdapter adapter)
{
    if(!adapter) unreachable();
    adapter->refCount ++;
}

void wgpuAdapterRelease(WGPUAdapter adapter)
{
    if(!adapter) unreachable();
    adapter->refCount --;
    if(adapter->refCount < 1)
    {
        wasi_webgpu_webgpu_gpu_adapter_drop_own(adapter->adapter);
        free(adapter);
    }
}

// void wgpuAdapterInfoFreeMembers(WGPUAdapterInfo adapterInfo)
// {
// }

// void wgpuBindGroupSetLabel(WGPUBindGroup bindGroup, WGPUStringView label)
// {
// }

// void wgpuBindGroupAddRef(WGPUBindGroup bindGroup)
// {
// }

// void wgpuBindGroupRelease(WGPUBindGroup bindGroup)
// {
// }

// void wgpuBindGroupLayoutSetLabel(WGPUBindGroupLayout bindGroupLayout, WGPUStringView label)
// {
// }

// void wgpuBindGroupLayoutAddRef(WGPUBindGroupLayout bindGroupLayout)
// {
// }

// void wgpuBindGroupLayoutRelease(WGPUBindGroupLayout bindGroupLayout)
// {
// }

// void wgpuBufferDestroy(WGPUBuffer buffer)
// {
// }

// void const* wgpuBufferGetConstMappedRange(WGPUBuffer buffer, size_t offset, size_t size)
// {
// }

// WGPUBufferMapState wgpuBufferGetMapState(WGPUBuffer buffer)
// {
// }

// void* wgpuBufferGetMappedRange(WGPUBuffer buffer, size_t offset, size_t size)
// {
// }

// uint64_t wgpuBufferGetSize(WGPUBuffer buffer)
// {
// }

// WGPUBufferUsage wgpuBufferGetUsage(WGPUBuffer buffer)
// {
// }

// WGPUFuture wgpuBufferMapAsync(WGPUBuffer buffer, WGPUMapMode mode, size_t offset, size_t size,
//     WGPUBufferMapCallbackInfo callbackInfo)
// {
// }

// WGPUStatus wgpuBufferReadMappedRange(WGPUBuffer buffer, size_t offset, void* data, size_t size)
// {
// }

// void wgpuBufferSetLabel(WGPUBuffer buffer, WGPUStringView label)
// {
// }

// void wgpuBufferUnmap(WGPUBuffer buffer)
// {
// }

// WGPUStatus wgpuBufferWriteMappedRange(WGPUBuffer buffer, size_t offset, void const* data, size_t size)
// {
// }

// void wgpuBufferAddRef(WGPUBuffer buffer)
// {
// }

// void wgpuBufferRelease(WGPUBuffer buffer)
// {
// }

// void wgpuCommandBufferSetLabel(WGPUCommandBuffer commandBuffer, WGPUStringView label)
// {
// }

// void wgpuCommandBufferAddRef(WGPUCommandBuffer commandBuffer)
// {
// }

// void wgpuCommandBufferRelease(WGPUCommandBuffer commandBuffer)
// {
// }

// WGPUComputePassEncoder wgpuCommandEncoderBeginComputePass(WGPUCommandEncoder commandEncoder,
//     WGPUComputePassDescriptor const* descriptor)
// {
// }

// WGPURenderPassEncoder wgpuCommandEncoderBeginRenderPass(WGPUCommandEncoder commandEncoder,
//     WGPURenderPassDescriptor const* descriptor)
// {
// }

// void wgpuCommandEncoderClearBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size)
// {
// }

// void wgpuCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset,
//     WGPUBuffer destination, uint64_t destinationOffset, uint64_t size)
// {
// }

// void wgpuCommandEncoderCopyBufferToTexture(WGPUCommandEncoder commandEncoder, WGPUTexelCopyBufferInfo const* source,
//     WGPUTexelCopyTextureInfo const* destination, WGPUExtent3D const* copySize)
// {
// }

// void wgpuCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder commandEncoder, WGPUTexelCopyTextureInfo const* source,
//     WGPUTexelCopyBufferInfo const* destination, WGPUExtent3D const* copySize)
// {
// }

// void wgpuCommandEncoderCopyTextureToTexture(WGPUCommandEncoder commandEncoder, WGPUTexelCopyTextureInfo const* source,
//     WGPUTexelCopyTextureInfo const* destination, WGPUExtent3D const* copySize)
// {
// }

// WGPUCommandBuffer wgpuCommandEncoderFinish(WGPUCommandEncoder commandEncoder,
//     WGPUCommandBufferDescriptor const* descriptor)
// {
// }

// void wgpuCommandEncoderInsertDebugMarker(WGPUCommandEncoder commandEncoder, WGPUStringView markerLabel)
// {
// }

// void wgpuCommandEncoderPopDebugGroup(WGPUCommandEncoder commandEncoder)
// {
// }

// void wgpuCommandEncoderPushDebugGroup(WGPUCommandEncoder commandEncoder, WGPUStringView groupLabel)
// {
// }

// void wgpuCommandEncoderResolveQuerySet(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t firstQuery,
//     uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset)
// {
// }

// void wgpuCommandEncoderSetLabel(WGPUCommandEncoder commandEncoder, WGPUStringView label)
// {
// }

// void wgpuCommandEncoderWriteTimestamp(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t queryIndex)
// {
// }

// void wgpuCommandEncoderAddRef(WGPUCommandEncoder commandEncoder)
// {
// }

// void wgpuCommandEncoderRelease(WGPUCommandEncoder commandEncoder)
// {
// }

// void wgpuComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder computePassEncoder, uint32_t workgroupCountX,
//     uint32_t workgroupCountY, uint32_t workgroupCountZ)
// {
// }

// void wgpuComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder computePassEncoder,
//     WGPUBuffer indirectBuffer, uint64_t indirectOffset)
// {
// }

// void wgpuComputePassEncoderEnd(WGPUComputePassEncoder computePassEncoder)
// {
// }

// void wgpuComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder computePassEncoder, WGPUStringView markerLabel)
// {
// }

// void wgpuComputePassEncoderPopDebugGroup(WGPUComputePassEncoder computePassEncoder)
// {
// }

// void wgpuComputePassEncoderPushDebugGroup(WGPUComputePassEncoder computePassEncoder, WGPUStringView groupLabel)
// {
// }

// void wgpuComputePassEncoderSetBindGroup(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex,
//     WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const* dynamicOffsets)
// {
// }

// void wgpuComputePassEncoderSetLabel(WGPUComputePassEncoder computePassEncoder, WGPUStringView label)
// {
// }

// void wgpuComputePassEncoderSetPipeline(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline)
// {
// }

// void wgpuComputePassEncoderAddRef(WGPUComputePassEncoder computePassEncoder)
// {
// }

// void wgpuComputePassEncoderRelease(WGPUComputePassEncoder computePassEncoder)
// {
// }

// WGPUBindGroupLayout wgpuComputePipelineGetBindGroupLayout(WGPUComputePipeline computePipeline, uint32_t groupIndex)
// {
// }

// void wgpuComputePipelineSetLabel(WGPUComputePipeline computePipeline, WGPUStringView label)
// {
// }

// void wgpuComputePipelineAddRef(WGPUComputePipeline computePipeline)
// {
// }

// void wgpuComputePipelineRelease(WGPUComputePipeline computePipeline)
// {
// }

// WGPUBindGroup wgpuDeviceCreateBindGroup(WGPUDevice device, WGPUBindGroupDescriptor const* descriptor)
// {
// }

// WGPUBindGroupLayout wgpuDeviceCreateBindGroupLayout(WGPUDevice device, WGPUBindGroupLayoutDescriptor const* descriptor)
// {
// }

// WGPUBuffer wgpuDeviceCreateBuffer(WGPUDevice device, WGPUBufferDescriptor const* descriptor)
// {
// }

// WGPUCommandEncoder wgpuDeviceCreateCommandEncoder(WGPUDevice device, WGPUCommandEncoderDescriptor const* descriptor)
// {
// }

// WGPUComputePipeline wgpuDeviceCreateComputePipeline(WGPUDevice device, WGPUComputePipelineDescriptor const* descriptor)
// {
// }

// WGPUFuture wgpuDeviceCreateComputePipelineAsync(WGPUDevice device, WGPUComputePipelineDescriptor const* descriptor,
//     WGPUCreateComputePipelineAsyncCallbackInfo callbackInfo)
// {
// }

// WGPUPipelineLayout wgpuDeviceCreatePipelineLayout(WGPUDevice device, WGPUPipelineLayoutDescriptor const* descriptor)
// {
// }

// WGPUQuerySet wgpuDeviceCreateQuerySet(WGPUDevice device, WGPUQuerySetDescriptor const* descriptor)
// {
// }

// WGPURenderBundleEncoder wgpuDeviceCreateRenderBundleEncoder(WGPUDevice device,
//     WGPURenderBundleEncoderDescriptor const* descriptor)
// {
// }

// WGPURenderPipeline wgpuDeviceCreateRenderPipeline(WGPUDevice device, WGPURenderPipelineDescriptor const* descriptor)
// {
// }

// WGPUFuture wgpuDeviceCreateRenderPipelineAsync(WGPUDevice device, WGPURenderPipelineDescriptor const* descriptor,
//     WGPUCreateRenderPipelineAsyncCallbackInfo callbackInfo)
// {
// }

// WGPUSampler wgpuDeviceCreateSampler(WGPUDevice device, WGPUSamplerDescriptor const* descriptor)
// {
// }

// WGPUShaderModule wgpuDeviceCreateShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const* descriptor)
// {
// }

// WGPUTexture wgpuDeviceCreateTexture(WGPUDevice device, WGPUTextureDescriptor const* descriptor)
// {
// }

// void wgpuDeviceDestroy(WGPUDevice device)
// {
// }

// WGPUStatus wgpuDeviceGetAdapterInfo(WGPUDevice device, WGPUAdapterInfo* adapterInfo)
// {
// }

// void wgpuDeviceGetFeatures(WGPUDevice device, WGPUSupportedFeatures* features)
// {
// }

// WGPUStatus wgpuDeviceGetLimits(WGPUDevice device, WGPULimits* limits)
// {
// }

// WGPUFuture wgpuDeviceGetLostFuture(WGPUDevice device)
// {
// }

// WGPUQueue wgpuDeviceGetQueue(WGPUDevice device)
// {
// }

// WGPUBool wgpuDeviceHasFeature(WGPUDevice device, WGPUFeatureName feature)
// {
// }

// WGPUFuture wgpuDevicePopErrorScope(WGPUDevice device, WGPUPopErrorScopeCallbackInfo callbackInfo)
// {
// }

// void wgpuDevicePushErrorScope(WGPUDevice device, WGPUErrorFilter filter)
// {
// }

// void wgpuDeviceSetLabel(WGPUDevice device, WGPUStringView label)
// {
// }

void wgpuDeviceAddRef(WGPUDevice device)
{
    if(!device) unreachable();
    device->refCount ++;
}

void wgpuDeviceRelease(WGPUDevice device)
{
    if(!device) unreachable();
    device->refCount --;
    if(device->refCount < 1)
    {
        wasi_webgpu_webgpu_gpu_device_drop_own(device->device);
        free(device);
    }
}

// WGPUSurface wgpuInstanceCreateSurface(WGPUInstance instance, WGPUSurfaceDescriptor const* descriptor)
// {
// }

// WGPUStatus wgpuInstanceGetWGSLLanguageFeatures(WGPUInstance instance, WGPUSupportedWGSLLanguageFeatures* features)
// {
// }

// WGPUBool wgpuInstanceHasWGSLLanguageFeature(WGPUInstance instance, WGPUWGSLLanguageFeatureName feature)
// {
// }

// void wgpuInstanceProcessEvents(WGPUInstance instance)
// {
// }

WGPUFuture wgpuInstanceRequestAdapter(WGPUInstance instance, WGPURequestAdapterOptions const* options,
    WGPURequestAdapterCallbackInfo callbackInfo)
{
    if(!instance) unreachable();

    wasi_webgpu_webgpu_gpu_request_adapter_options_t wasi_options = {};
    if (options)
    {
        wasi_options.feature_level = featureLevelNativeToWasi(options->featureLevel);
        wasi_options.power_preference = powerPreferenceNativeToWasi(options->powerPreference);
        wasi_options.force_fallback_adapter.is_some = true;
        wasi_options.force_fallback_adapter.val = options->forceFallbackAdapter;
    }
    // TODO: set xr_compatible

    wasi_webgpu_webgpu_own_gpu_adapter_t wasi_adapter;
    bool success = wasi_webgpu_webgpu_method_gpu_request_adapter(
        wasi_webgpu_webgpu_borrow_gpu(instance->gpu),
        &wasi_options,
        &wasi_adapter
    );

    if (!success)
    {
        todo();
    }

    WGPUAdapterImpl * adapter = malloc(sizeof(WGPUAdapterImpl));
    adapter->refCount = 1;
    adapter->adapter = wasi_adapter;

    wasi_webgpu_webgpu_gpu_request_adapter_options_free(&wasi_options);

    callbackInfo.callback(WGPURequestAdapterStatus_Success, adapter, WGPU_STRING_VIEW_INIT, NULL, NULL);
    return (WGPUFuture) { .id = -1 };
}

// WGPUWaitStatus wgpuInstanceWaitAny(WGPUInstance instance, size_t futureCount, WGPUFutureWaitInfo* futures,
//     uint64_t timeoutNS)
// {
// }

void wgpuInstanceAddRef(WGPUInstance instance)
{
    if(!instance) unreachable();
    instance->refCount ++;
}

void wgpuInstanceRelease(WGPUInstance instance)
{
    if(!instance) unreachable();
    instance->refCount --;
    if(instance->refCount < 1)
    {
        wasi_webgpu_webgpu_gpu_drop_own(instance->gpu);
        free(instance);
    }
}

// void wgpuPipelineLayoutSetLabel(WGPUPipelineLayout pipelineLayout, WGPUStringView label)
// {
// }

// void wgpuPipelineLayoutAddRef(WGPUPipelineLayout pipelineLayout)
// {
// }

// void wgpuPipelineLayoutRelease(WGPUPipelineLayout pipelineLayout)
// {
// }

// void wgpuQuerySetDestroy(WGPUQuerySet querySet)
// {
// }

// uint32_t wgpuQuerySetGetCount(WGPUQuerySet querySet)
// {
// }

// WGPUQueryType wgpuQuerySetGetType(WGPUQuerySet querySet)
// {
// }

// void wgpuQuerySetSetLabel(WGPUQuerySet querySet, WGPUStringView label)
// {
// }

// void wgpuQuerySetAddRef(WGPUQuerySet querySet)
// {
// }

// void wgpuQuerySetRelease(WGPUQuerySet querySet)
// {
// }

// WGPUFuture wgpuQueueOnSubmittedWorkDone(WGPUQueue queue, WGPUQueueWorkDoneCallbackInfo callbackInfo)
// {
// }

// void wgpuQueueSetLabel(WGPUQueue queue, WGPUStringView label)
// {
// }

// void wgpuQueueSubmit(WGPUQueue queue, size_t commandCount, WGPUCommandBuffer const* commands)
// {
// }

// void wgpuQueueWriteBuffer(WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const* data, size_t size)
// {
// }

// void wgpuQueueWriteTexture(WGPUQueue queue, WGPUTexelCopyTextureInfo const* destination, void const* data, size_t dataSize,
//     WGPUTexelCopyBufferLayout const* dataLayout, WGPUExtent3D const* writeSize)
// {
// }

// void wgpuQueueAddRef(WGPUQueue queue)
// {
// }

// void wgpuQueueRelease(WGPUQueue queue)
// {
// }

// void wgpuRenderBundleSetLabel(WGPURenderBundle renderBundle, WGPUStringView label)
// {
// }

// void wgpuRenderBundleAddRef(WGPURenderBundle renderBundle)
// {
// }

// void wgpuRenderBundleRelease(WGPURenderBundle renderBundle)
// {
// }

// void wgpuRenderBundleEncoderDraw(WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount,
//     uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
// {
// }

// void wgpuRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount,
//     uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance)
// {
// }

// void wgpuRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer,
//     uint64_t indirectOffset)
// {
// }

// void wgpuRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer,
//     uint64_t indirectOffset)
// {
// }

// WGPURenderBundle wgpuRenderBundleEncoderFinish(WGPURenderBundleEncoder renderBundleEncoder,
//     WGPURenderBundleDescriptor const* descriptor)
// {
// }

// void wgpuRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView markerLabel)
// {
// }

// void wgpuRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder renderBundleEncoder)
// {
// }

// void wgpuRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView groupLabel)
// {
// }

// void wgpuRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder renderBundleEncoder, uint32_t groupIndex,
//     WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const* dynamicOffsets)
// {
// }

// void wgpuRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer,
//     WGPUIndexFormat format, uint64_t offset, uint64_t size)
// {
// }

// void wgpuRenderBundleEncoderSetLabel(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView label)
// {
// }

// void wgpuRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderPipeline pipeline)
// {
// }

// void wgpuRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder renderBundleEncoder, uint32_t slot,
//     WGPUBuffer buffer, uint64_t offset, uint64_t size)
// {
// }

// void wgpuRenderBundleEncoderAddRef(WGPURenderBundleEncoder renderBundleEncoder)
// {
// }

// void wgpuRenderBundleEncoderRelease(WGPURenderBundleEncoder renderBundleEncoder)
// {
// }

// void wgpuRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder renderPassEncoder, uint32_t queryIndex)
// {
// }

// void wgpuRenderPassEncoderDraw(WGPURenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount,
//     uint32_t firstVertex, uint32_t firstInstance)
// {
// }

// void wgpuRenderPassEncoderDrawIndexed(WGPURenderPassEncoder renderPassEncoder, uint32_t indexCount,
//     uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance)
// {
// }

// void wgpuRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer,
//     uint64_t indirectOffset)
// {
// }

// void wgpuRenderPassEncoderDrawIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer,
//     uint64_t indirectOffset)
// {
// }

// void wgpuRenderPassEncoderEnd(WGPURenderPassEncoder renderPassEncoder)
// {
// }

// void wgpuRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder renderPassEncoder)
// {
// }

// void wgpuRenderPassEncoderExecuteBundles(WGPURenderPassEncoder renderPassEncoder, size_t bundleCount,
//     WGPURenderBundle const* bundles)
// {
// }

// void wgpuRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder renderPassEncoder, WGPUStringView markerLabel)
// {
// }

// void wgpuRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder renderPassEncoder)
// {
// }

// void wgpuRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder renderPassEncoder, WGPUStringView groupLabel)
// {
// }

// void wgpuRenderPassEncoderSetBindGroup(WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex,
//     WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const* dynamicOffsets)
// {
// }

// void wgpuRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder renderPassEncoder, WGPUColor const* color)
// {
// }

// void wgpuRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer,
//     WGPUIndexFormat format, uint64_t offset, uint64_t size)
// {
// }

// void wgpuRenderPassEncoderSetLabel(WGPURenderPassEncoder renderPassEncoder, WGPUStringView label)
// {
// }

// void wgpuRenderPassEncoderSetPipeline(WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline)
// {
// }

// void wgpuRenderPassEncoderSetScissorRect(WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y,
//     uint32_t width, uint32_t height)
// {
// }

// void wgpuRenderPassEncoderSetStencilReference(WGPURenderPassEncoder renderPassEncoder, uint32_t reference)
// {
// }

// void wgpuRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder renderPassEncoder, uint32_t slot, WGPUBuffer buffer,
//     uint64_t offset, uint64_t size)
// {
// }

// void wgpuRenderPassEncoderSetViewport(WGPURenderPassEncoder renderPassEncoder, float x, float y, float width,
//     float height, float minDepth, float maxDepth)
// {
// }

// void wgpuRenderPassEncoderAddRef(WGPURenderPassEncoder renderPassEncoder)
// {
// }

// void wgpuRenderPassEncoderRelease(WGPURenderPassEncoder renderPassEncoder)
// {
// }

// WGPUBindGroupLayout wgpuRenderPipelineGetBindGroupLayout(WGPURenderPipeline renderPipeline, uint32_t groupIndex)
// {
// }

// void wgpuRenderPipelineSetLabel(WGPURenderPipeline renderPipeline, WGPUStringView label)
// {
// }

// void wgpuRenderPipelineAddRef(WGPURenderPipeline renderPipeline)
// {
// }

// void wgpuRenderPipelineRelease(WGPURenderPipeline renderPipeline)
// {
// }

// void wgpuSamplerSetLabel(WGPUSampler sampler, WGPUStringView label)
// {
// }

// void wgpuSamplerAddRef(WGPUSampler sampler)
// {
// }

// void wgpuSamplerRelease(WGPUSampler sampler)
// {
// }

// WGPUFuture wgpuShaderModuleGetCompilationInfo(WGPUShaderModule shaderModule,
//     WGPUCompilationInfoCallbackInfo callbackInfo)
// {
// }

// void wgpuShaderModuleSetLabel(WGPUShaderModule shaderModule, WGPUStringView label)
// {
// }

// void wgpuShaderModuleAddRef(WGPUShaderModule shaderModule)
// {
// }

// void wgpuShaderModuleRelease(WGPUShaderModule shaderModule)
// {
// }

// void wgpuSupportedFeaturesFreeMembers(WGPUSupportedFeatures supportedFeatures)
// {
// }

// void wgpuSupportedWGSLLanguageFeaturesFreeMembers(WGPUSupportedWGSLLanguageFeatures supportedWGSLLanguageFeatures)
// {
// }

// void wgpuSurfaceConfigure(WGPUSurface surface, WGPUSurfaceConfiguration const* config)
// {
// }

// WGPUStatus wgpuSurfaceGetCapabilities(WGPUSurface surface, WGPUAdapter adapter, WGPUSurfaceCapabilities* capabilities)
// {
// }

// void wgpuSurfaceGetCurrentTexture(WGPUSurface surface, WGPUSurfaceTexture* surfaceTexture)
// {
// }

// WGPUStatus wgpuSurfacePresent(WGPUSurface surface)
// {
// }

// void wgpuSurfaceSetLabel(WGPUSurface surface, WGPUStringView label)
// {
// }

// void wgpuSurfaceUnconfigure(WGPUSurface surface)
// {
// }

// void wgpuSurfaceAddRef(WGPUSurface surface)
// {
// }

// void wgpuSurfaceRelease(WGPUSurface surface)
// {
// }

// void wgpuSurfaceCapabilitiesFreeMembers(WGPUSurfaceCapabilities surfaceCapabilities)
// {
// }

// WGPUTextureView wgpuTextureCreateView(WGPUTexture texture, WGPUTextureViewDescriptor const* descriptor)
// {
// }

// void wgpuTextureDestroy(WGPUTexture texture)
// {
// }

// uint32_t wgpuTextureGetDepthOrArrayLayers(WGPUTexture texture)
// {
// }

// WGPUTextureDimension wgpuTextureGetDimension(WGPUTexture texture)
// {
// }

// WGPUTextureFormat wgpuTextureGetFormat(WGPUTexture texture)
// {
// }

// uint32_t wgpuTextureGetHeight(WGPUTexture texture)
// {
// }

// uint32_t wgpuTextureGetMipLevelCount(WGPUTexture texture)
// {
// }

// uint32_t wgpuTextureGetSampleCount(WGPUTexture texture)
// {
// }

// WGPUTextureUsage wgpuTextureGetUsage(WGPUTexture texture)
// {
// }

// uint32_t wgpuTextureGetWidth(WGPUTexture texture)
// {
// }

// void wgpuTextureSetLabel(WGPUTexture texture, WGPUStringView label)
// {
// }

// void wgpuTextureAddRef(WGPUTexture texture)
// {
// }

// void wgpuTextureRelease(WGPUTexture texture)
// {
// }

// void wgpuTextureViewSetLabel(WGPUTextureView textureView, WGPUStringView label)
// {
// }

// void wgpuTextureViewAddRef(WGPUTextureView textureView)
// {
// }

// void wgpuTextureViewRelease(WGPUTextureView textureView)
// {
// }

imports_option_string_t featureLevelNativeToWasi(WGPUFeatureLevel featureLevel)
{
    const char* compatibility = "compatibility";
    const char* core = "core";

    imports_option_string_t output = {};
    if (featureLevel == WGPUFeatureLevel_Undefined) {
        return output;
    }

    output.is_some = true;
    switch (featureLevel) {
        case WGPUFeatureLevel_Compatibility:
            output.val.ptr = malloc(strlen(compatibility));
            memcpy(output.val.ptr, compatibility, strlen(compatibility));
            output.val.len = strlen(compatibility);
            break;
        case WGPUFeatureLevel_Core:
            output.val.ptr = malloc(strlen(core));
            memcpy(output.val.ptr, core, strlen(core));
            output.val.len = strlen(core);
            break;
        default:
            unreachable();
    }
    return output;
}

wasi_webgpu_webgpu_option_gpu_power_preference_t powerPreferenceNativeToWasi(WGPUPowerPreference powerPreference)
{
    wasi_webgpu_webgpu_option_gpu_power_preference_t output = {};
    if (powerPreference == WGPUPowerPreference_Undefined) {
        return output;
    }

    output.is_some = true;
    switch (powerPreference) {
        case WGPUPowerPreference_LowPower:
            output.val = WASI_WEBGPU_WEBGPU_GPU_POWER_PREFERENCE_LOW_POWER;
            break;
        case WGPUPowerPreference_HighPerformance:
            output.val = WASI_WEBGPU_WEBGPU_GPU_POWER_PREFERENCE_HIGH_PERFORMANCE;
            break;
        default:
            unreachable();
    }
    return output;
}

wasi_webgpu_webgpu_gpu_feature_name_t featureNativeToWasi(WGPUFeatureName const feature)
{
    switch (feature) {
        case WGPUFeatureName_DepthClipControl:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_DEPTH_CLIP_CONTROL;
        case WGPUFeatureName_Depth32FloatStencil8:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_DEPTH32FLOAT_STENCIL8;
        case WGPUFeatureName_TextureCompressionBC:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_TEXTURE_COMPRESSION_BC;
        case WGPUFeatureName_TextureCompressionBCSliced3D:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_TEXTURE_COMPRESSION_BC_SLICED3D;
        case WGPUFeatureName_TextureCompressionETC2:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_TEXTURE_COMPRESSION_ETC2;
        case WGPUFeatureName_TextureCompressionASTC:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_TEXTURE_COMPRESSION_ASTC;
        case WGPUFeatureName_TextureCompressionASTCSliced3D:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_TEXTURE_COMPRESSION_ASTC_SLICED3D;
        case WGPUFeatureName_TimestampQuery:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_TIMESTAMP_QUERY;
        case WGPUFeatureName_IndirectFirstInstance:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_INDIRECT_FIRST_INSTANCE;
        case WGPUFeatureName_ShaderF16:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_SHADER_F16;
        case WGPUFeatureName_RG11B10UfloatRenderable:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_RG11B10UFLOAT_RENDERABLE;
        case WGPUFeatureName_BGRA8UnormStorage:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_BGRA8UNORM_STORAGE;
        case WGPUFeatureName_Float32Filterable:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_FLOAT32_FILTERABLE;
        case WGPUFeatureName_Float32Blendable:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_FLOAT32_BLENDABLE;
        case WGPUFeatureName_ClipDistances:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_CLIP_DISTANCES;
        case WGPUFeatureName_DualSourceBlending:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_DUAL_SOURCE_BLENDING;
        case WGPUFeatureName_Subgroups:
            return WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_SUBGROUPS;
        default:
            unreachable();
    }
}

WGPUFeatureName featureWasiToNative(wasi_webgpu_webgpu_gpu_feature_name_t const feature)
{
    switch (feature) {
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_DEPTH_CLIP_CONTROL:
            return WGPUFeatureName_DepthClipControl;
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_DEPTH32FLOAT_STENCIL8:
            return WGPUFeatureName_Depth32FloatStencil8;
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_TEXTURE_COMPRESSION_BC:
            return WGPUFeatureName_TextureCompressionBC;
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_TEXTURE_COMPRESSION_BC_SLICED3D:
            return WGPUFeatureName_TextureCompressionBCSliced3D;
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_TEXTURE_COMPRESSION_ETC2:
            return WGPUFeatureName_TextureCompressionETC2;
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_TEXTURE_COMPRESSION_ASTC:
            return WGPUFeatureName_TextureCompressionASTC;
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_TEXTURE_COMPRESSION_ASTC_SLICED3D:
            return WGPUFeatureName_TextureCompressionASTCSliced3D;
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_TIMESTAMP_QUERY:
            return WGPUFeatureName_TimestampQuery;
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_INDIRECT_FIRST_INSTANCE:
            return WGPUFeatureName_IndirectFirstInstance;
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_SHADER_F16:
            return WGPUFeatureName_ShaderF16;
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_RG11B10UFLOAT_RENDERABLE:
            return WGPUFeatureName_RG11B10UfloatRenderable;
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_BGRA8UNORM_STORAGE:
            return WGPUFeatureName_BGRA8UnormStorage;
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_FLOAT32_FILTERABLE:
            return WGPUFeatureName_Float32Filterable;
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_FLOAT32_BLENDABLE:
            return WGPUFeatureName_Float32Blendable;
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_CLIP_DISTANCES:
            return WGPUFeatureName_ClipDistances;
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_DUAL_SOURCE_BLENDING:
            return WGPUFeatureName_DualSourceBlending;
        case WASI_WEBGPU_WEBGPU_GPU_FEATURE_NAME_SUBGROUPS:
            return WGPUFeatureName_Subgroups;
        default:
            return WGPUFeatureName_Undefined;
    }
}

wasi_webgpu_webgpu_option_own_record_option_gpu_size64_t limitsNativeToWasi(WGPULimits const* limits_native)
{
    wasi_webgpu_webgpu_option_own_record_option_gpu_size64_t output = {};
    if (!limits_native) {
        return output;
    }

    output.is_some = true;
    output.val = wasi_webgpu_webgpu_constructor_record_option_gpu_size64();
    wasi_webgpu_webgpu_borrow_record_option_gpu_size64_t limits_wasi_borrow = wasi_webgpu_webgpu_borrow_record_option_gpu_size64(output.val);

    if (limits_native->maxTextureDimension1D != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-texture-dimension1-d";
        str.len = strlen((char*)str.ptr);
        uint64_t maxTextureDimension1D = (uint64_t)limits_native->maxTextureDimension1D;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxTextureDimension1D
        );
    }
    if (limits_native->maxTextureDimension2D != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-texture-dimension2-d";
        str.len = strlen((char*)str.ptr);
        uint64_t maxTextureDimension2D = (uint64_t)limits_native->maxTextureDimension2D;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxTextureDimension2D
        );
    }
    if (limits_native->maxTextureDimension3D != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-texture-dimension3-d";
        str.len = strlen((char*)str.ptr);
        uint64_t maxTextureDimension3D = (uint64_t)limits_native->maxTextureDimension3D;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxTextureDimension3D
        );
    }
    if (limits_native->maxTextureArrayLayers != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-texture-array-layers";
        str.len = strlen((char*)str.ptr);
        uint64_t maxTextureArrayLayers = (uint64_t)limits_native->maxTextureArrayLayers;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxTextureArrayLayers
        );
    }
    if (limits_native->maxBindGroups != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-bind-groups";
        str.len = strlen((char*)str.ptr);
        uint64_t maxBindGroups = (uint64_t)limits_native->maxBindGroups;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxBindGroups
        );
    }
    if (limits_native->maxBindGroupsPlusVertexBuffers != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-bind-groups-plus-vertex-buffers";
        str.len = strlen((char*)str.ptr);
        uint64_t maxBindGroupsPlusVertexBuffers = (uint64_t)limits_native->maxBindGroupsPlusVertexBuffers;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxBindGroupsPlusVertexBuffers
        );
    }
    if (limits_native->maxBindingsPerBindGroup != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-bindings-per-bind-group";
        str.len = strlen((char*)str.ptr);
        uint64_t maxBindingsPerBindGroup = (uint64_t)limits_native->maxBindingsPerBindGroup;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxBindingsPerBindGroup
        );
    }
    if (limits_native->maxDynamicUniformBuffersPerPipelineLayout != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-dynamic-uniform-buffers-per-pipeline-layout";
        str.len = strlen((char*)str.ptr);
        uint64_t maxDynamicUniformBuffersPerPipelineLayout = (uint64_t)limits_native->maxDynamicUniformBuffersPerPipelineLayout;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxDynamicUniformBuffersPerPipelineLayout
        );
    }
    if (limits_native->maxDynamicStorageBuffersPerPipelineLayout != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-dynamic-storage-buffers-per-pipeline-layout";
        str.len = strlen((char*)str.ptr);
        uint64_t maxDynamicStorageBuffersPerPipelineLayout = (uint64_t)limits_native->maxDynamicStorageBuffersPerPipelineLayout;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxDynamicStorageBuffersPerPipelineLayout
        );
    }
    if (limits_native->maxSampledTexturesPerShaderStage != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-sampled-textures-per-shader-stage";
        str.len = strlen((char*)str.ptr);
        uint64_t maxSampledTexturesPerShaderStage = (uint64_t)limits_native->maxSampledTexturesPerShaderStage;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxSampledTexturesPerShaderStage
        );
    }
    if (limits_native->maxSamplersPerShaderStage != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-samplers-per-shader-stage";
        str.len = strlen((char*)str.ptr);
        uint64_t maxSamplersPerShaderStage = (uint64_t)limits_native->maxSamplersPerShaderStage;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxSamplersPerShaderStage
        );
    }
    if (limits_native->maxStorageBuffersPerShaderStage != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-storage-buffers-per-shader-stage";
        str.len = strlen((char*)str.ptr);
        uint64_t maxStorageBuffersPerShaderStage = (uint64_t)limits_native->maxStorageBuffersPerShaderStage;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxStorageBuffersPerShaderStage
        );
    }
    if (limits_native->maxStorageTexturesPerShaderStage != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-storage-textures-per-shader-stage";
        str.len = strlen((char*)str.ptr);
        uint64_t maxStorageTexturesPerShaderStage = (uint64_t)limits_native->maxStorageTexturesPerShaderStage;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxStorageTexturesPerShaderStage
        );
    }
    if (limits_native->maxUniformBuffersPerShaderStage != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-uniform-buffers-per-shader-stage";
        str.len = strlen((char*)str.ptr);
        uint64_t maxUniformBuffersPerShaderStage = (uint64_t)limits_native->maxUniformBuffersPerShaderStage;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxUniformBuffersPerShaderStage
        );
    }
    if (limits_native->maxUniformBufferBindingSize != WGPU_LIMIT_U64_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-uniform-buffer-binding-size";
        str.len = strlen((char*)str.ptr);
        uint64_t maxUniformBufferBindingSize = limits_native->maxUniformBufferBindingSize;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxUniformBufferBindingSize
        );
    }
    if (limits_native->maxStorageBufferBindingSize != WGPU_LIMIT_U64_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-storage-buffer-binding-size";
        str.len = strlen((char*)str.ptr);
        uint64_t maxStorageBufferBindingSize = limits_native->maxStorageBufferBindingSize;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxStorageBufferBindingSize
        );
    }
    if (limits_native->minUniformBufferOffsetAlignment != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"min-uniform-buffer-offset-alignment";
        str.len = strlen((char*)str.ptr);
        uint64_t minUniformBufferOffsetAlignment = (uint64_t)limits_native->minUniformBufferOffsetAlignment;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &minUniformBufferOffsetAlignment
        );
    }
    if (limits_native->minStorageBufferOffsetAlignment != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"min-storage-buffer-offset-alignment";
        str.len = strlen((char*)str.ptr);
        uint64_t minStorageBufferOffsetAlignment = (uint64_t)limits_native->minStorageBufferOffsetAlignment;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &minStorageBufferOffsetAlignment
        );
    }
    if (limits_native->maxVertexBuffers != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-vertex-buffers";
        str.len = strlen((char*)str.ptr);
        uint64_t maxVertexBuffers = (uint64_t)limits_native->maxVertexBuffers;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxVertexBuffers
        );
    }
    if (limits_native->maxBufferSize != WGPU_LIMIT_U64_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-buffer-size";
        str.len = strlen((char*)str.ptr);
        uint64_t maxBufferSize = limits_native->maxBufferSize;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxBufferSize
        );
    }
    if (limits_native->maxVertexAttributes != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-vertex-attributes";
        str.len = strlen((char*)str.ptr);
        uint64_t maxVertexAttributes = (uint64_t)limits_native->maxVertexAttributes;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxVertexAttributes
        );
    }
    if (limits_native->maxVertexBufferArrayStride != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-vertex-buffer-array-stride";
        str.len = strlen((char*)str.ptr);
        uint64_t maxVertexBufferArrayStride = (uint64_t)limits_native->maxVertexBufferArrayStride;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxVertexBufferArrayStride
        );
    }
    if (limits_native->maxInterStageShaderVariables != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-inter-stage-shader-variables";
        str.len = strlen((char*)str.ptr);
        uint64_t maxInterStageShaderVariables = (uint64_t)limits_native->maxInterStageShaderVariables;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxInterStageShaderVariables
        );
    }
    if (limits_native->maxColorAttachments != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-color-attachments";
        str.len = strlen((char*)str.ptr);
        uint64_t maxColorAttachments = (uint64_t)limits_native->maxColorAttachments;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxColorAttachments
        );
    }
    if (limits_native->maxColorAttachmentBytesPerSample != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-color-attachment-bytes-per-sample";
        str.len = strlen((char*)str.ptr);
        uint64_t maxColorAttachmentBytesPerSample = (uint64_t)limits_native->maxColorAttachmentBytesPerSample;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxColorAttachmentBytesPerSample
        );
    }
    if (limits_native->maxComputeWorkgroupStorageSize != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-compute-workgroup-storage-size";
        str.len = strlen((char*)str.ptr);
        uint64_t maxComputeWorkgroupStorageSize = (uint64_t)limits_native->maxComputeWorkgroupStorageSize;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxComputeWorkgroupStorageSize
        );
    }
    if (limits_native->maxComputeInvocationsPerWorkgroup != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-compute-invocations-per-workgroup";
        str.len = strlen((char*)str.ptr);
        uint64_t maxComputeInvocationsPerWorkgroup = (uint64_t)limits_native->maxComputeInvocationsPerWorkgroup;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxComputeInvocationsPerWorkgroup
        );
    }
    if (limits_native->maxComputeWorkgroupSizeX != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-compute-workgroup-size-x";
        str.len = strlen((char*)str.ptr);
        uint64_t maxComputeWorkgroupSizeX = (uint64_t)limits_native->maxComputeWorkgroupSizeX;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxComputeWorkgroupSizeX
        );
    }
    if (limits_native->maxComputeWorkgroupSizeY != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-compute-workgroup-size-y";
        str.len = strlen((char*)str.ptr);
        uint64_t maxComputeWorkgroupSizeY = (uint64_t)limits_native->maxComputeWorkgroupSizeY;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxComputeWorkgroupSizeY
        );
    }
    if (limits_native->maxComputeWorkgroupSizeZ != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-compute-workgroup-size-z";
        str.len = strlen((char*)str.ptr);
        uint64_t maxComputeWorkgroupSizeZ = (uint64_t)limits_native->maxComputeWorkgroupSizeZ;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxComputeWorkgroupSizeZ
        );
    }
    if (limits_native->maxComputeWorkgroupsPerDimension != WGPU_LIMIT_U32_UNDEFINED)
    {
        imports_string_t str = {};
        str.ptr = (uint8_t*)"max-compute-workgroups-per-dimension";
        str.len = strlen((char*)str.ptr);
        uint64_t maxComputeWorkgroupsPerDimension = (uint64_t)limits_native->maxComputeWorkgroupsPerDimension;
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(
            limits_wasi_borrow,
            &str,
            &maxComputeWorkgroupsPerDimension
        );
    }

    return output;
}
