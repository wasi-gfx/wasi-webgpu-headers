#include "webgpu/webgpu.h"

#include <stdlib.h>
#include <string.h>

#include "imports.h"

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
    wasi_webgpu_webgpu_gpu_device_descriptor_t descriptor_impl = {};

    // This is stubbed out - there are a signficiant number of options yet to be supported

    if (descriptor->requiredLimits)
    {
        WGPULimits const* limits = descriptor->requiredLimits;

        descriptor_impl.required_limits.is_some = true;
        descriptor_impl.required_limits.val = wasi_webgpu_webgpu_constructor_record_option_gpu_size64();
        wasi_webgpu_webgpu_borrow_record_option_gpu_size64_t limits_ref =
            wasi_webgpu_webgpu_borrow_record_option_gpu_size64(descriptor_impl.required_limits.val);

        if (limits->maxBindGroups)
        {
            imports_string_t str = {};
            str.ptr = (uint8_t*)"maxBindGroups";
            str.len = strlen((char*)str.ptr);
            uint64_t maxBindGroups = limits->maxBindGroups;
            wasi_webgpu_webgpu_method_record_option_gpu_size64_add(limits_ref, &str, &maxBindGroups);
        }
        if (limits->maxBindGroupsPlusVertexBuffers)
        {
            imports_string_t str = {};
            str.ptr = (uint8_t*)"maxBindGroupsPlusVertexBuffers";
            str.len = strlen((char*)str.ptr);
            uint64_t maxBindGroupsPlusVertexBuffers = limits->maxBindGroupsPlusVertexBuffers;
            wasi_webgpu_webgpu_method_record_option_gpu_size64_add(limits_ref, &str, &maxBindGroupsPlusVertexBuffers);
        }
        // ...

        wasi_webgpu_webgpu_record_option_gpu_size64_drop_own(descriptor_impl.required_limits.val);
    }

    wasi_webgpu_webgpu_own_gpu_device_t dev;
    wasi_webgpu_webgpu_request_device_error_t err;
    bool success = wasi_webgpu_webgpu_method_gpu_adapter_request_device(
        wasi_webgpu_webgpu_borrow_gpu_adapter(adapter->adapter),
        descriptor ? &descriptor_impl : NULL,
        &dev,
        &err
    );

    WGPUDeviceImpl * device = malloc(sizeof(WGPUDeviceImpl));
    device->refCount = 1;
    device->device = dev;

    WGPURequestDeviceCallback callback = callbackInfo.callback;
    callback(WGPURequestDeviceStatus_Success, device, WGPU_STRING_VIEW_INIT, callbackInfo.userdata1, callbackInfo.userdata2);
    return (WGPUFuture) { .id = -1 };
}

void wgpuAdapterAddRef(WGPUAdapter adapter)
{
    adapter->refCount ++;
}

void wgpuAdapterRelease(WGPUAdapter adapter)
{
    adapter->refCount --;
    if(adapter->refCount < 1)
    {
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
    device->refCount ++;
}

void wgpuDeviceRelease(WGPUDevice device)
{
    device->refCount --;
    if(device->refCount < 1)
    {
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
    wasi_webgpu_webgpu_gpu_request_adapter_options_t wasi_options = {};
    wasi_webgpu_webgpu_own_gpu_adapter_t wasi_adapter;

    bool success = wasi_webgpu_webgpu_method_gpu_request_adapter(
        wasi_webgpu_webgpu_borrow_gpu(instance->gpu),
        &wasi_options,
        &wasi_adapter
    );

    WGPUAdapterImpl * adapter = malloc(sizeof(WGPUAdapterImpl));
    adapter->refCount = 1;
    adapter->adapter = wasi_adapter;

    callbackInfo.callback(WGPURequestAdapterStatus_Success, adapter, WGPU_STRING_VIEW_INIT, NULL, NULL);
    return (WGPUFuture) { .id = -1 };
}

// WGPUWaitStatus wgpuInstanceWaitAny(WGPUInstance instance, size_t futureCount, WGPUFutureWaitInfo* futures,
//     uint64_t timeoutNS)
// {
// }

void wgpuInstanceAddRef(WGPUInstance instance)
{
    instance->refCount ++;
}

void wgpuInstanceRelease(WGPUInstance instance)
{
    instance->refCount --;
    if(instance->refCount < 1)
    {
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
