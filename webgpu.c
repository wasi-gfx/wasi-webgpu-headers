#include "webgpu/webgpu.h"

#include <stdlib.h>
#include <string.h>

#include "imports.h"


WGPUInstance wgpuCreateInstance(WGPUInstanceDescriptor const* descriptor)
{
    exit(1);
}

void wgpuGetInstanceFeatures(WGPUInstanceFeatures* features)
{
    exit(1);
}

WGPUProc wgpuGetProcAddress(char const* procName)
{
    exit(1);
}

WGPUStatus wgpuAdapterGetFeatures(WGPUAdapter adapter, WGPUSupportedFeatures* features)
{
    exit(1);
}

void wgpuAdapterGetInfo(WGPUAdapter adapter, WGPUAdapterInfo* info)
{
    exit(1);
}

WGPUBool wgpuAdapterGetLimits(WGPUAdapter adapter, WGPUSupportedLimits* limits)
{
    exit(1);
}

WGPUBool wgpuAdapterHasFeature(WGPUAdapter adapter, WGPUFeatureName feature)
{
    exit(1);
}

WGPUFuture wgpuAdapterRequestDevice(WGPUAdapter adapter, WGPUDeviceDescriptor const* descriptor,
    WGPURequestDeviceCallbackInfo callbackInfo)
{
    wasi_webgpu_webgpu_gpu_device_descriptor_t descriptor_impl = {};

    // This is stubbed out - there are a signficiant number of options yet to be supported

    if (descriptor->requiredLimits)
    {
        WGPULimits* limits = &descriptor->requiredLimits->limits;

        descriptor_impl.required_limits.is_some = true;
        descriptor_impl.required_limits.val = wasi_webgpu_webgpu_constructor_record_gpu_size64();
        wasi_webgpu_webgpu_borrow_record_gpu_size64_t limits_ref = 
            wasi_webgpu_webgpu_borrow_record_gpu_size64(descriptor_impl.required_limits.val);

        //limits_ref->maxBindGroups
        if (limits->maxBindGroups)
        {
            imports_string_t str = {};
            str.ptr = "maxBindGroups";
            str.len = strlen(str.ptr);
            wasi_webgpu_webgpu_method_record_gpu_size64_add(limits_ref, &str,limits->maxBindGroups);
        }
        if (limits->maxBindGroupsPlusVertexBuffers)
        {
            imports_string_t str = {};
            str.ptr = "maxBindGroupsPlusVertexBuffers";
            str.len = strlen(str.ptr);
            wasi_webgpu_webgpu_method_record_gpu_size64_add(limits_ref, &str,limits->maxBindGroupsPlusVertexBuffers);
        }
        // ...

        wasi_webgpu_webgpu_record_gpu_size64_drop_own(descriptor_impl.required_limits.val);

    }
    
    wasi_webgpu_webgpu_own_gpu_adapter_t adapter_own = {};
    adapter_own.__handle = (int32_t)adapter;

    wasi_webgpu_webgpu_borrow_gpu_adapter_t adapter_borrow = 
        wasi_webgpu_webgpu_borrow_gpu_adapter(adapter_own);

    wasi_webgpu_webgpu_own_gpu_device_t dev = wasi_webgpu_webgpu_method_gpu_adapter_request_device(
        adapter_borrow, descriptor ? &descriptor_impl : NULL
    );

    WGPUDevice device = (WGPUDevice)dev.__handle;
    
    WGPURequestDeviceCallback callback = callbackInfo.callback;
    callback(WGPURequestDeviceStatus_Success, device, NULL, callbackInfo.userdata1, callbackInfo.userdata2);
    
    WGPUFuture ret = {-1};
    return ret;
}

void wgpuAdapterAddRef(WGPUAdapter adapter)
{
    exit(1);
}

void wgpuAdapterRelease(WGPUAdapter adapter)
{
    exit(1);
}

void wgpuAdapterInfoFreeMembers(WGPUAdapterInfo adapterInfo)
{
    exit(1);
}

void wgpuBindGroupSetLabel(WGPUBindGroup bindGroup, char const* label)
{
    exit(1);
}

void wgpuBindGroupAddRef(WGPUBindGroup bindGroup)
{
    exit(1);
}

void wgpuBindGroupRelease(WGPUBindGroup bindGroup)
{
    exit(1);
}

void wgpuBindGroupLayoutSetLabel(WGPUBindGroupLayout bindGroupLayout, char const* label)
{
    exit(1);
}

void wgpuBindGroupLayoutAddRef(WGPUBindGroupLayout bindGroupLayout)
{
    exit(1);
}

void wgpuBindGroupLayoutRelease(WGPUBindGroupLayout bindGroupLayout)
{
    exit(1);
}

void wgpuBufferDestroy(WGPUBuffer buffer)
{
    exit(1);
}

void const* wgpuBufferGetConstMappedRange(WGPUBuffer buffer, size_t offset, size_t size)
{
    exit(1);
}

WGPUBufferMapState wgpuBufferGetMapState(WGPUBuffer buffer)
{
    exit(1);
}

void* wgpuBufferGetMappedRange(WGPUBuffer buffer, size_t offset, size_t size)
{
    exit(1);
}

uint64_t wgpuBufferGetSize(WGPUBuffer buffer)
{
    exit(1);
}

WGPUBufferUsage wgpuBufferGetUsage(WGPUBuffer buffer)
{
    exit(1);
}

WGPUFuture wgpuBufferMapAsync(WGPUBuffer buffer, WGPUMapMode mode, size_t offset, size_t size,
    WGPUBufferMapCallbackInfo callbackInfo)
{
    exit(1);
}

void wgpuBufferSetLabel(WGPUBuffer buffer, char const* label)
{
    exit(1);
}

void wgpuBufferUnmap(WGPUBuffer buffer)
{
    exit(1);
}

void wgpuBufferAddRef(WGPUBuffer buffer)
{
    exit(1);
}

void wgpuBufferRelease(WGPUBuffer buffer)
{
    exit(1);
}

void wgpuCommandBufferSetLabel(WGPUCommandBuffer commandBuffer, char const* label)
{
    exit(1);
}

void wgpuCommandBufferAddRef(WGPUCommandBuffer commandBuffer)
{
    exit(1);
}

void wgpuCommandBufferRelease(WGPUCommandBuffer commandBuffer)
{
    exit(1);
}

WGPUComputePassEncoder wgpuCommandEncoderBeginComputePass(WGPUCommandEncoder commandEncoder,
    WGPUComputePassDescriptor const* descriptor)
{
    exit(1);
}

WGPURenderPassEncoder wgpuCommandEncoderBeginRenderPass(WGPUCommandEncoder commandEncoder,
    WGPURenderPassDescriptor const* descriptor)
{
    exit(1);
}

void wgpuCommandEncoderClearBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size)
{
    exit(1);
}

void wgpuCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset,
    WGPUBuffer destination, uint64_t destinationOffset, uint64_t size)
{
    exit(1);
}

void wgpuCommandEncoderCopyBufferToTexture(WGPUCommandEncoder commandEncoder, WGPUImageCopyBuffer const* source,
    WGPUImageCopyTexture const* destination, WGPUExtent3D const* copySize)
{
    exit(1);
}

void wgpuCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const* source,
    WGPUImageCopyBuffer const* destination, WGPUExtent3D const* copySize)
{
    exit(1);
}

void wgpuCommandEncoderCopyTextureToTexture(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const* source,
    WGPUImageCopyTexture const* destination, WGPUExtent3D const* copySize)
{
    exit(1);
}

WGPUCommandBuffer wgpuCommandEncoderFinish(WGPUCommandEncoder commandEncoder,
    WGPUCommandBufferDescriptor const* descriptor)
{
    exit(1);
}

void wgpuCommandEncoderInsertDebugMarker(WGPUCommandEncoder commandEncoder, char const* markerLabel)
{
    exit(1);
}

void wgpuCommandEncoderPopDebugGroup(WGPUCommandEncoder commandEncoder)
{
    exit(1);
}

void wgpuCommandEncoderPushDebugGroup(WGPUCommandEncoder commandEncoder, char const* groupLabel)
{
    exit(1);
}

void wgpuCommandEncoderResolveQuerySet(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t firstQuery,
    uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset)
{
    exit(1);
}

void wgpuCommandEncoderSetLabel(WGPUCommandEncoder commandEncoder, char const* label)
{
    exit(1);
}

void wgpuCommandEncoderWriteTimestamp(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t queryIndex)
{
    exit(1);
}

void wgpuCommandEncoderAddRef(WGPUCommandEncoder commandEncoder)
{
    exit(1);
}

void wgpuCommandEncoderRelease(WGPUCommandEncoder commandEncoder)
{
    exit(1);
}

void wgpuComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder computePassEncoder, uint32_t workgroupCountX,
    uint32_t workgroupCountY, uint32_t workgroupCountZ)
{
    exit(1);
}

void wgpuComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder computePassEncoder,
    WGPUBuffer indirectBuffer, uint64_t indirectOffset)
{
    exit(1);
}

void wgpuComputePassEncoderEnd(WGPUComputePassEncoder computePassEncoder)
{
    exit(1);
}

void wgpuComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder computePassEncoder, char const* markerLabel)
{
    exit(1);
}

void wgpuComputePassEncoderPopDebugGroup(WGPUComputePassEncoder computePassEncoder)
{
    exit(1);
}

void wgpuComputePassEncoderPushDebugGroup(WGPUComputePassEncoder computePassEncoder, char const* groupLabel)
{
    exit(1);
}

void wgpuComputePassEncoderSetBindGroup(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex,
    WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const* dynamicOffsets)
{
    exit(1);
}

void wgpuComputePassEncoderSetLabel(WGPUComputePassEncoder computePassEncoder, char const* label)
{
    exit(1);
}

void wgpuComputePassEncoderSetPipeline(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline)
{
    exit(1);
}

void wgpuComputePassEncoderAddRef(WGPUComputePassEncoder computePassEncoder)
{
    exit(1);
}

void wgpuComputePassEncoderRelease(WGPUComputePassEncoder computePassEncoder)
{
    exit(1);
}

WGPUBindGroupLayout wgpuComputePipelineGetBindGroupLayout(WGPUComputePipeline computePipeline, uint32_t groupIndex)
{
    exit(1);
}

void wgpuComputePipelineSetLabel(WGPUComputePipeline computePipeline, char const* label)
{
    exit(1);
}

void wgpuComputePipelineAddRef(WGPUComputePipeline computePipeline)
{
    exit(1);
}

void wgpuComputePipelineRelease(WGPUComputePipeline computePipeline)
{
    exit(1);
}

WGPUBindGroup wgpuDeviceCreateBindGroup(WGPUDevice device, WGPUBindGroupDescriptor const* descriptor)
{
    exit(1);
}

WGPUBindGroupLayout wgpuDeviceCreateBindGroupLayout(WGPUDevice device, WGPUBindGroupLayoutDescriptor const* descriptor)
{
    exit(1);
}

WGPUBuffer wgpuDeviceCreateBuffer(WGPUDevice device, WGPUBufferDescriptor const* descriptor)
{
    exit(1);
}

WGPUCommandEncoder wgpuDeviceCreateCommandEncoder(WGPUDevice device, WGPUCommandEncoderDescriptor const* descriptor)
{
    exit(1);
}

WGPUComputePipeline wgpuDeviceCreateComputePipeline(WGPUDevice device, WGPUComputePipelineDescriptor const* descriptor)
{
    exit(1);
}

WGPUFuture wgpuDeviceCreateComputePipelineAsync(WGPUDevice device, WGPUComputePipelineDescriptor const* descriptor,
    WGPUCreateComputePipelineAsyncCallbackInfo callbackInfo)
{
    exit(1);
}

WGPUPipelineLayout wgpuDeviceCreatePipelineLayout(WGPUDevice device, WGPUPipelineLayoutDescriptor const* descriptor)
{
    exit(1);
}

WGPUQuerySet wgpuDeviceCreateQuerySet(WGPUDevice device, WGPUQuerySetDescriptor const* descriptor)
{
    exit(1);
}

WGPURenderBundleEncoder wgpuDeviceCreateRenderBundleEncoder(WGPUDevice device,
    WGPURenderBundleEncoderDescriptor const* descriptor)
{
    exit(1);
}

WGPURenderPipeline wgpuDeviceCreateRenderPipeline(WGPUDevice device, WGPURenderPipelineDescriptor const* descriptor)
{
    exit(1);
}

WGPUFuture wgpuDeviceCreateRenderPipelineAsync(WGPUDevice device, WGPURenderPipelineDescriptor const* descriptor,
    WGPUCreateRenderPipelineAsyncCallbackInfo callbackInfo)
{
    exit(1);
}

WGPUSampler wgpuDeviceCreateSampler(WGPUDevice device, WGPUSamplerDescriptor const* descriptor)
{
    exit(1);
}

WGPUShaderModule wgpuDeviceCreateShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const* descriptor)
{
    exit(1);
}

WGPUTexture wgpuDeviceCreateTexture(WGPUDevice device, WGPUTextureDescriptor const* descriptor)
{
    exit(1);
}

void wgpuDeviceDestroy(WGPUDevice device)
{
    exit(1);
}

WGPUStatus wgpuDeviceGetFeatures(WGPUDevice device, WGPUSupportedFeatures* features)
{
    exit(1);
}

WGPUBool wgpuDeviceGetLimits(WGPUDevice device, WGPUSupportedLimits* limits)
{
    exit(1);
}

WGPUQueue wgpuDeviceGetQueue(WGPUDevice device)
{
    exit(1);
}

WGPUBool wgpuDeviceHasFeature(WGPUDevice device, WGPUFeatureName feature)
{
    exit(1);
}

WGPUFuture wgpuDevicePopErrorScope(WGPUDevice device, WGPUPopErrorScopeCallbackInfo callbackInfo)
{
    exit(1);
}

void wgpuDevicePushErrorScope(WGPUDevice device, WGPUErrorFilter filter)
{
    exit(1);
}

void wgpuDeviceSetLabel(WGPUDevice device, char const* label)
{
    exit(1);
}

void wgpuDeviceAddRef(WGPUDevice device)
{
    exit(1);
}

void wgpuDeviceRelease(WGPUDevice device)
{
    exit(1);
}

WGPUSurface wgpuInstanceCreateSurface(WGPUInstance instance, WGPUSurfaceDescriptor const* descriptor)
{
    exit(1);
}

WGPUBool wgpuInstanceHasWGSLLanguageFeature(WGPUInstance instance, WGPUWGSLFeatureName feature)
{
    exit(1);
}

void wgpuInstanceProcessEvents(WGPUInstance instance)
{
    exit(1);
}

WGPUFuture wgpuInstanceRequestAdapter(WGPUInstance instance, WGPURequestAdapterOptions const* options,
    WGPURequestAdapterCallbackInfo callbackInfo)
{
    exit(1);
}

WGPUWaitStatus wgpuInstanceWaitAny(WGPUInstance instance, size_t futureCount, WGPUFutureWaitInfo* futures,
    uint64_t timeoutNS)
{
    exit(1);
}

void wgpuInstanceAddRef(WGPUInstance instance)
{
    exit(1);
}

void wgpuInstanceRelease(WGPUInstance instance)
{
    exit(1);
}

void wgpuPipelineLayoutSetLabel(WGPUPipelineLayout pipelineLayout, char const* label)
{
    exit(1);
}

void wgpuPipelineLayoutAddRef(WGPUPipelineLayout pipelineLayout)
{
    exit(1);
}

void wgpuPipelineLayoutRelease(WGPUPipelineLayout pipelineLayout)
{
    exit(1);
}

void wgpuQuerySetDestroy(WGPUQuerySet querySet)
{
    exit(1);
}

uint32_t wgpuQuerySetGetCount(WGPUQuerySet querySet)
{
    exit(1);
}

WGPUQueryType wgpuQuerySetGetType(WGPUQuerySet querySet)
{
    exit(1);
}

void wgpuQuerySetSetLabel(WGPUQuerySet querySet, char const* label)
{
    exit(1);
}

void wgpuQuerySetAddRef(WGPUQuerySet querySet)
{
    exit(1);
}

void wgpuQuerySetRelease(WGPUQuerySet querySet)
{
    exit(1);
}

WGPUFuture wgpuQueueOnSubmittedWorkDone(WGPUQueue queue, WGPUQueueWorkDoneCallbackInfo callbackInfo)
{
    exit(1);
}

void wgpuQueueSetLabel(WGPUQueue queue, char const* label)
{
    exit(1);
}

void wgpuQueueSubmit(WGPUQueue queue, size_t commandCount, WGPUCommandBuffer const* commands)
{
    exit(1);
}

void wgpuQueueWriteBuffer(WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const* data, size_t size)
{
    exit(1);
}

void wgpuQueueWriteTexture(WGPUQueue queue, WGPUImageCopyTexture const* destination, void const* data, size_t dataSize,
    WGPUTextureDataLayout const* dataLayout, WGPUExtent3D const* writeSize)
{
    exit(1);
}

void wgpuQueueAddRef(WGPUQueue queue)
{
    exit(1);
}

void wgpuQueueRelease(WGPUQueue queue)
{
    exit(1);
}

void wgpuRenderBundleSetLabel(WGPURenderBundle renderBundle, char const* label)
{
    exit(1);
}

void wgpuRenderBundleAddRef(WGPURenderBundle renderBundle)
{
    exit(1);
}

void wgpuRenderBundleRelease(WGPURenderBundle renderBundle)
{
    exit(1);
}

void wgpuRenderBundleEncoderDraw(WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount,
    uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
{
    exit(1);
}

void wgpuRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount,
    uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance)
{
    exit(1);
}

void wgpuRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer,
    uint64_t indirectOffset)
{
    exit(1);
}

void wgpuRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer,
    uint64_t indirectOffset)
{
    exit(1);
}

WGPURenderBundle wgpuRenderBundleEncoderFinish(WGPURenderBundleEncoder renderBundleEncoder,
    WGPURenderBundleDescriptor const* descriptor)
{
    exit(1);
}

void wgpuRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder renderBundleEncoder, char const* markerLabel)
{
    exit(1);
}

void wgpuRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder renderBundleEncoder)
{
    exit(1);
}

void wgpuRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder renderBundleEncoder, char const* groupLabel)
{
    exit(1);
}

void wgpuRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder renderBundleEncoder, uint32_t groupIndex,
    WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const* dynamicOffsets)
{
    exit(1);
}

void wgpuRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer,
    WGPUIndexFormat format, uint64_t offset, uint64_t size)
{
    exit(1);
}

void wgpuRenderBundleEncoderSetLabel(WGPURenderBundleEncoder renderBundleEncoder, char const* label)
{
    exit(1);
}

void wgpuRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderPipeline pipeline)
{
    exit(1);
}

void wgpuRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder renderBundleEncoder, uint32_t slot,
    WGPUBuffer buffer, uint64_t offset, uint64_t size)
{
    exit(1);
}

void wgpuRenderBundleEncoderAddRef(WGPURenderBundleEncoder renderBundleEncoder)
{
    exit(1);
}

void wgpuRenderBundleEncoderRelease(WGPURenderBundleEncoder renderBundleEncoder)
{
    exit(1);
}

void wgpuRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder renderPassEncoder, uint32_t queryIndex)
{
    exit(1);
}

void wgpuRenderPassEncoderDraw(WGPURenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount,
    uint32_t firstVertex, uint32_t firstInstance)
{
    exit(1);
}

void wgpuRenderPassEncoderDrawIndexed(WGPURenderPassEncoder renderPassEncoder, uint32_t indexCount,
    uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance)
{
    exit(1);
}

void wgpuRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer,
    uint64_t indirectOffset)
{
    exit(1);
}

void wgpuRenderPassEncoderDrawIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer,
    uint64_t indirectOffset)
{
    exit(1);
}

void wgpuRenderPassEncoderEnd(WGPURenderPassEncoder renderPassEncoder)
{
    exit(1);
}

void wgpuRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder renderPassEncoder)
{
    exit(1);
}

void wgpuRenderPassEncoderExecuteBundles(WGPURenderPassEncoder renderPassEncoder, size_t bundleCount,
    WGPURenderBundle const* bundles)
{
    exit(1);
}

void wgpuRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder renderPassEncoder, char const* markerLabel)
{
    exit(1);
}

void wgpuRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder renderPassEncoder)
{
    exit(1);
}

void wgpuRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder renderPassEncoder, char const* groupLabel)
{
    exit(1);
}

void wgpuRenderPassEncoderSetBindGroup(WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex,
    WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const* dynamicOffsets)
{
    exit(1);
}

void wgpuRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder renderPassEncoder, WGPUColor const* color)
{
    exit(1);
}

void wgpuRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer,
    WGPUIndexFormat format, uint64_t offset, uint64_t size)
{
    exit(1);
}

void wgpuRenderPassEncoderSetLabel(WGPURenderPassEncoder renderPassEncoder, char const* label)
{
    exit(1);
}

void wgpuRenderPassEncoderSetPipeline(WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline)
{
    exit(1);
}

void wgpuRenderPassEncoderSetScissorRect(WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y,
    uint32_t width, uint32_t height)
{
    exit(1);
}

void wgpuRenderPassEncoderSetStencilReference(WGPURenderPassEncoder renderPassEncoder, uint32_t reference)
{
    exit(1);
}

void wgpuRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder renderPassEncoder, uint32_t slot, WGPUBuffer buffer,
    uint64_t offset, uint64_t size)
{
    exit(1);
}

void wgpuRenderPassEncoderSetViewport(WGPURenderPassEncoder renderPassEncoder, float x, float y, float width,
    float height, float minDepth, float maxDepth)
{
    exit(1);
}

void wgpuRenderPassEncoderAddRef(WGPURenderPassEncoder renderPassEncoder)
{
    exit(1);
}

void wgpuRenderPassEncoderRelease(WGPURenderPassEncoder renderPassEncoder)
{
    exit(1);
}

WGPUBindGroupLayout wgpuRenderPipelineGetBindGroupLayout(WGPURenderPipeline renderPipeline, uint32_t groupIndex)
{
    exit(1);
}

void wgpuRenderPipelineSetLabel(WGPURenderPipeline renderPipeline, char const* label)
{
    exit(1);
}

void wgpuRenderPipelineAddRef(WGPURenderPipeline renderPipeline)
{
    exit(1);
}

void wgpuRenderPipelineRelease(WGPURenderPipeline renderPipeline)
{
    exit(1);
}

void wgpuSamplerSetLabel(WGPUSampler sampler, char const* label)
{
    exit(1);
}

void wgpuSamplerAddRef(WGPUSampler sampler)
{
    exit(1);
}

void wgpuSamplerRelease(WGPUSampler sampler)
{
    exit(1);
}

WGPUFuture wgpuShaderModuleGetCompilationInfo(WGPUShaderModule shaderModule,
    WGPUCompilationInfoCallbackInfo callbackInfo)
{
    exit(1);
}

void wgpuShaderModuleSetLabel(WGPUShaderModule shaderModule, char const* label)
{
    exit(1);
}

void wgpuShaderModuleAddRef(WGPUShaderModule shaderModule)
{
    exit(1);
}

void wgpuShaderModuleRelease(WGPUShaderModule shaderModule)
{
    exit(1);
}

void wgpuSupportedFeaturesFreeMembers(WGPUSupportedFeatures supportedFeatures)
{
    exit(1);
}

void wgpuSurfaceConfigure(WGPUSurface surface, WGPUSurfaceConfiguration const* config)
{
    exit(1);
}

WGPUBool wgpuSurfaceGetCapabilities(WGPUSurface surface, WGPUAdapter adapter, WGPUSurfaceCapabilities* capabilities)
{
    exit(1);
}

void wgpuSurfaceGetCurrentTexture(WGPUSurface surface, WGPUSurfaceTexture* surfaceTexture)
{
    exit(1);
}

void wgpuSurfacePresent(WGPUSurface surface)
{
    exit(1);
}

void wgpuSurfaceSetLabel(WGPUSurface surface, char const* label)
{
    exit(1);
}

void wgpuSurfaceUnconfigure(WGPUSurface surface)
{
    exit(1);
}

void wgpuSurfaceAddRef(WGPUSurface surface)
{
    exit(1);
}

void wgpuSurfaceRelease(WGPUSurface surface)
{
    exit(1);
}

void wgpuSurfaceCapabilitiesFreeMembers(WGPUSurfaceCapabilities surfaceCapabilities)
{
    exit(1);
}

WGPUTextureView wgpuTextureCreateView(WGPUTexture texture, WGPUTextureViewDescriptor const* descriptor)
{
    exit(1);
}

void wgpuTextureDestroy(WGPUTexture texture)
{
    exit(1);
}

uint32_t wgpuTextureGetDepthOrArrayLayers(WGPUTexture texture)
{
    exit(1);
}

WGPUTextureDimension wgpuTextureGetDimension(WGPUTexture texture)
{
    exit(1);
}

WGPUTextureFormat wgpuTextureGetFormat(WGPUTexture texture)
{
    exit(1);
}

uint32_t wgpuTextureGetHeight(WGPUTexture texture)
{
    exit(1);
}

uint32_t wgpuTextureGetMipLevelCount(WGPUTexture texture)
{
    exit(1);
}

uint32_t wgpuTextureGetSampleCount(WGPUTexture texture)
{
    exit(1);
}

WGPUTextureUsage wgpuTextureGetUsage(WGPUTexture texture)
{
    exit(1);
}

uint32_t wgpuTextureGetWidth(WGPUTexture texture)
{
    exit(1);
}

void wgpuTextureSetLabel(WGPUTexture texture, char const* label)
{
    exit(1);
}

void wgpuTextureAddRef(WGPUTexture texture)
{
    exit(1);
}

void wgpuTextureRelease(WGPUTexture texture)
{
    exit(1);
}

void wgpuTextureViewSetLabel(WGPUTextureView textureView, char const* label)
{
    exit(1);
}

void wgpuTextureViewAddRef(WGPUTextureView textureView)
{
    exit(1);
}

void wgpuTextureViewRelease(WGPUTextureView textureView)
{
    exit(1);
}
