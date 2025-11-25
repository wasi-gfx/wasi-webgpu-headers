#include "webgpu/webgpu.h"

#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

#include "imports.h"

noreturn void todo() { abort(); }

noreturn void unreachable() { abort(); }

typedef struct WGPUAdapterImpl {
    wasi_webgpu_webgpu_own_gpu_adapter_t adapter;
    uint32_t refCount;
} WGPUAdapterImpl;
typedef struct WGPUBindGroupImpl {
    wasi_webgpu_webgpu_own_gpu_bind_group_t bind_group;
    uint32_t refCount;
} WGPUBindGroupImpl;
typedef struct WGPUBindGroupLayoutImpl {
    wasi_webgpu_webgpu_own_gpu_bind_group_layout_t bind_group_layout;
    uint32_t refCount;
} WGPUBindGroupLayoutImpl;
typedef struct WGPUBufferImpl {
    wasi_webgpu_webgpu_own_gpu_buffer_t buffer;
    uint32_t refCount;
    imports_list_u8_t* mapping;
    uint64_t offset;
} WGPUBufferImpl;
typedef struct WGPUCommandBufferImpl {
    wasi_webgpu_webgpu_own_gpu_command_buffer_t command_buffer;
    uint32_t refCount;
} WGPUCommandBufferImpl;
typedef struct WGPUCommandEncoderImpl {
    wasi_webgpu_webgpu_own_gpu_command_encoder_t command_encoder;
    uint32_t refCount;
} WGPUCommandEncoderImpl;
typedef struct WGPUComputePassEncoderImpl {
    wasi_webgpu_webgpu_own_gpu_compute_pass_encoder_t compute_pass_encoder;
    uint32_t refCount;
} WGPUComputePassEncoderImpl;
typedef struct WGPUComputePipelineImpl {
    wasi_webgpu_webgpu_own_gpu_compute_pipeline_t compute_pipeline;
    uint32_t refCount;
} WGPUComputePipelineImpl;
typedef struct WGPUDeviceImpl {
    wasi_webgpu_webgpu_own_gpu_device_t device;
    uint32_t refCount;
} WGPUDeviceImpl;
typedef struct WGPUInstanceImpl {
    wasi_webgpu_webgpu_own_gpu_t gpu;
    uint32_t refCount;
} WGPUInstanceImpl;
typedef struct WGPUPipelineLayoutImpl {
    wasi_webgpu_webgpu_own_gpu_pipeline_layout_t pipeline_layout;
    uint32_t refCount;
} WGPUPipelineLayoutImpl;
typedef struct WGPUQuerySetImpl {
    wasi_webgpu_webgpu_own_gpu_query_set_t query_set;
    uint32_t refCount;
} WGPUQuerySetImpl;
typedef struct WGPUQueueImpl {
    wasi_webgpu_webgpu_own_gpu_queue_t queue;
    uint32_t refCount;
} WGPUQueueImpl;
typedef struct WGPURenderBundleImpl {
    wasi_webgpu_webgpu_own_gpu_render_bundle_t render_bundle;
    uint32_t refCount;
} WGPURenderBundleImpl;
typedef struct WGPURenderBundleEncoderImpl {
    wasi_webgpu_webgpu_own_gpu_render_bundle_encoder_t render_bundle_encoder;
    uint32_t refCount;
} WGPURenderBundleEncoderImpl;
typedef struct WGPURenderPassEncoderImpl {
    wasi_webgpu_webgpu_own_gpu_render_pass_encoder_t render_pass_encoder;
    uint32_t refCount;
} WGPURenderPassEncoderImpl;
typedef struct WGPURenderPipelineImpl {
    wasi_webgpu_webgpu_own_gpu_render_pipeline_t render_pipeline;
    uint32_t refCount;
} WGPURenderPipelineImpl;
typedef struct WGPUSamplerImpl {
    wasi_webgpu_webgpu_own_gpu_sampler_t sampler;
    uint32_t refCount;
} WGPUSamplerImpl;
typedef struct WGPUShaderModuleImpl {
    wasi_webgpu_webgpu_own_gpu_shader_module_t module;
    uint32_t refCount;
} WGPUShaderModuleImpl;
// typedef struct WGPUSurfaceImpl {
// } WGPUSurfaceImpl;
typedef struct WGPUTextureImpl {
    wasi_webgpu_webgpu_own_gpu_texture_t texture;
    uint32_t refCount;
} WGPUTextureImpl;
typedef struct WGPUTextureViewImpl {
    wasi_webgpu_webgpu_own_gpu_texture_view_t texture_view;
    uint32_t refCount;
} WGPUTextureViewImpl;

imports_option_string_t labelNativeToWasi(WGPUStringView const* label);
imports_option_string_t featureLevelNativeToWasi(WGPUFeatureLevel featureLevel);
wasi_webgpu_webgpu_option_gpu_power_preference_t powerPreferenceNativeToWasi(WGPUPowerPreference powerPreference);
wasi_webgpu_webgpu_gpu_feature_name_t featureNativeToWasi(WGPUFeatureName const feature);
imports_string_t featureNativeToWasiString(WGPUFeatureName const feature);
WGPUFeatureName featureWasiToNative(wasi_webgpu_webgpu_gpu_feature_name_t const feature);
wasi_webgpu_webgpu_option_own_record_option_gpu_size64_t limitsNativeToWasi(WGPULimits const* limits_native);
wasi_webgpu_webgpu_gpu_buffer_map_state_t bufferMapStateNativeToWasi(WGPUBufferMapState const bufferMapState);
WGPUBufferMapState bufferMapStateWasiToNative(wasi_webgpu_webgpu_gpu_buffer_map_state_t const buffer_map_state);

WGPUInstance wgpuCreateInstance(WGPUInstanceDescriptor const* descriptor) {
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

WGPUBool wgpuAdapterHasFeature(WGPUAdapter adapter, WGPUFeatureName feature) {
    imports_string_t feature_wasi_string = featureNativeToWasiString(feature);
    wasi_webgpu_webgpu_own_gpu_supported_features_t available_features =
        wasi_webgpu_webgpu_method_gpu_adapter_features(wasi_webgpu_webgpu_borrow_gpu_adapter(adapter->adapter));
    bool has_feature = wasi_webgpu_webgpu_method_gpu_supported_features_has(
        wasi_webgpu_webgpu_borrow_gpu_supported_features(available_features),
        &feature_wasi_string
    );
    // Free allocated resources
    imports_string_free(&feature_wasi_string);
    wasi_webgpu_webgpu_gpu_supported_features_drop_own(available_features);
    return has_feature;
}

WGPUFuture wgpuAdapterRequestDevice(
    WGPUAdapter adapter,
    WGPUDeviceDescriptor const* descriptor,
    WGPURequestDeviceCallbackInfo callbackInfo
) {
    if (!adapter) unreachable();

    wasi_webgpu_webgpu_gpu_device_descriptor_t descriptor_wasi = {};

    if (descriptor) {
        descriptor_wasi.required_limits = limitsNativeToWasi(descriptor->requiredLimits);

        descriptor_wasi.label = labelNativeToWasi(&descriptor->label);

        if (descriptor->requiredFeatures) {
            descriptor_wasi.required_features.is_some = true;
            descriptor_wasi.required_features.val = (wasi_webgpu_webgpu_list_gpu_feature_name_t){
                .ptr = malloc(descriptor->requiredFeatureCount * sizeof(wasi_webgpu_webgpu_gpu_feature_name_t)),
                .len = descriptor->requiredFeatureCount,
            };

            for (size_t i = 0; i < descriptor->requiredFeatureCount; i++) {
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

    if (!success) {
        wasi_webgpu_webgpu_request_device_error_free(&err);
        todo();
    }

    WGPUDeviceImpl* device = malloc(sizeof(WGPUDeviceImpl));
    device->refCount = 1;
    device->device = wasi_device;

    wasi_webgpu_webgpu_gpu_device_descriptor_free(&descriptor_wasi);

    callbackInfo.callback(
        WGPURequestDeviceStatus_Success,
        device,
        WGPU_STRING_VIEW_INIT,
        callbackInfo.userdata1,
        callbackInfo.userdata2
    );
    return (WGPUFuture){.id = 0};
}

void wgpuAdapterAddRef(WGPUAdapter adapter) {
    if (!adapter) unreachable();
    adapter->refCount++;
}

void wgpuAdapterRelease(WGPUAdapter adapter) {
    if (!adapter) unreachable();
    adapter->refCount--;
    if (adapter->refCount < 0) unreachable();
    if (adapter->refCount == 0) {
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

void wgpuBindGroupAddRef(WGPUBindGroup bindGroup) {
    if (!bindGroup) unreachable();
    bindGroup->refCount++;
}

void wgpuBindGroupRelease(WGPUBindGroup bindGroup) {
    if (!bindGroup) unreachable();
    bindGroup->refCount--;
    if (bindGroup->refCount < 0) unreachable();
    if (bindGroup->refCount == 0) {
        wasi_webgpu_webgpu_gpu_bind_group_drop_own(bindGroup->bind_group);
        free(bindGroup);
    }
}

// void wgpuBindGroupLayoutSetLabel(WGPUBindGroupLayout bindGroupLayout, WGPUStringView label)
// {
// }

void wgpuBindGroupLayoutAddRef(WGPUBindGroupLayout bindGroupLayout) {
    if (!bindGroupLayout) unreachable();
    bindGroupLayout->refCount++;
}

void wgpuBindGroupLayoutRelease(WGPUBindGroupLayout bindGroupLayout) {
    if (!bindGroupLayout) unreachable();
    bindGroupLayout->refCount--;
    if (bindGroupLayout->refCount < 0) unreachable();
    if (bindGroupLayout->refCount == 0) {
        wasi_webgpu_webgpu_gpu_bind_group_layout_drop_own(bindGroupLayout->bind_group_layout);
        free(bindGroupLayout);
    }
}

// void wgpuBufferDestroy(WGPUBuffer buffer)
// {
// }

void const* wgpuBufferGetConstMappedRange(WGPUBuffer buffer, size_t offset, size_t size) {
    return wgpuBufferGetMappedRange(buffer, offset, size);
}

WGPUBufferMapState wgpuBufferGetMapState(WGPUBuffer buffer) {
    if (!buffer) unreachable();
    wasi_webgpu_webgpu_borrow_gpu_buffer_t buffer_borrowed = wasi_webgpu_webgpu_borrow_gpu_buffer(buffer->buffer);
    wasi_webgpu_webgpu_gpu_buffer_map_state_t state_wasi =
        wasi_webgpu_webgpu_method_gpu_buffer_map_state(buffer_borrowed);
    return bufferMapStateWasiToNative(state_wasi);
}

void* wgpuBufferGetMappedRange(WGPUBuffer buffer, size_t offset, size_t size) {
    if (!buffer) unreachable();

    wasi_webgpu_webgpu_gpu_size64_t offset_wasi = (wasi_webgpu_webgpu_gpu_size64_t)offset;
    wasi_webgpu_webgpu_gpu_size64_t size_wasi = (wasi_webgpu_webgpu_gpu_size64_t)size;
    if (size == WGPU_WHOLE_MAP_SIZE) {
        size_wasi = wgpuBufferGetSize(buffer) - offset;
    }

    imports_list_u8_t* mapping = malloc(sizeof(imports_list_u8_t));
    wasi_webgpu_webgpu_get_mapped_range_error_t err;

    bool success = wasi_webgpu_webgpu_method_gpu_buffer_get_mapped_range_get_with_copy(
        wasi_webgpu_webgpu_borrow_gpu_buffer(buffer->buffer),
        &offset_wasi,
        &size_wasi,
        mapping,
        &err
    );

    if (!success) {
        wasi_webgpu_webgpu_get_mapped_range_error_free(&err);
        todo();
    }

    buffer->mapping = mapping;
    buffer->offset = offset;
    return mapping->ptr;
}

uint64_t wgpuBufferGetSize(WGPUBuffer buffer) {
    if (!buffer) unreachable();
    return wasi_webgpu_webgpu_method_gpu_buffer_size(wasi_webgpu_webgpu_borrow_gpu_buffer(buffer->buffer));
}

WGPUBufferUsage wgpuBufferGetUsage(WGPUBuffer buffer) {
    if (!buffer) unreachable();
    wasi_webgpu_webgpu_gpu_flags_constant_t usage =
        wasi_webgpu_webgpu_method_gpu_buffer_usage(wasi_webgpu_webgpu_borrow_gpu_buffer(buffer->buffer));
    return usage;
}

WGPUFuture wgpuBufferMapAsync(
    WGPUBuffer buffer,
    WGPUMapMode mode,
    size_t offset,
    size_t size,
    WGPUBufferMapCallbackInfo callbackInfo
) {
    if (!buffer) unreachable();

    wasi_webgpu_webgpu_gpu_map_mode_flags_t mode_wasi = (uint32_t)mode;
    wasi_webgpu_webgpu_gpu_size64_t offset_wasi = (wasi_webgpu_webgpu_gpu_size64_t)offset;
    wasi_webgpu_webgpu_gpu_size64_t size_wasi = (wasi_webgpu_webgpu_gpu_size64_t)size;
    if (size == WGPU_WHOLE_MAP_SIZE) {
        size_wasi = wgpuBufferGetSize(buffer) - offset;
    }

    wasi_webgpu_webgpu_map_async_error_t err;
    bool success = wasi_webgpu_webgpu_method_gpu_buffer_map_async(
        wasi_webgpu_webgpu_borrow_gpu_buffer(buffer->buffer),
        mode_wasi,
        &offset_wasi,
        &size_wasi,
        &err
    );

    if (!success) {
        wasi_webgpu_webgpu_map_async_error_free(&err);
        todo();
    }

    callbackInfo
        .callback(WGPUMapAsyncStatus_Success, WGPU_STRING_VIEW_INIT, callbackInfo.userdata1, callbackInfo.userdata2);

    return (WGPUFuture){.id = 0};
}

// WGPUStatus wgpuBufferReadMappedRange(WGPUBuffer buffer, size_t offset, void* data, size_t size)
// {
// }

// void wgpuBufferSetLabel(WGPUBuffer buffer, WGPUStringView label)
// {
// }

void wgpuBufferUnmap(WGPUBuffer buffer) {
    if (!buffer) unreachable();

    // since we don't have memory mapping yet, we need to copy the mapped range back to the buffer before unmapping
    if (buffer->mapping) {
        wasi_webgpu_webgpu_get_mapped_range_error_t err_set;
        bool success_set = wasi_webgpu_webgpu_method_gpu_buffer_get_mapped_range_set_with_copy(
            wasi_webgpu_webgpu_borrow_gpu_buffer(buffer->buffer),
            buffer->mapping,
            &buffer->offset,
            NULL, // copy in the whole mapped range
            &err_set
        );

        if (!success_set) {
            wasi_webgpu_webgpu_get_mapped_range_error_free(&err_set);
            todo();
        }

        imports_list_u8_free(buffer->mapping);
        buffer->mapping = NULL;
    }

    wasi_webgpu_webgpu_unmap_error_t err_unmap;
    bool success_unmap =
        wasi_webgpu_webgpu_method_gpu_buffer_unmap(wasi_webgpu_webgpu_borrow_gpu_buffer(buffer->buffer), &err_unmap);

    if (!success_unmap) {
        wasi_webgpu_webgpu_unmap_error_free(&err_unmap);
        todo();
    }
}

// WGPUStatus wgpuBufferWriteMappedRange(WGPUBuffer buffer, size_t offset, void const* data, size_t size)
// {
// }

void wgpuBufferAddRef(WGPUBuffer buffer) {
    if (!buffer) unreachable();
    buffer->refCount++;
}

void wgpuBufferRelease(WGPUBuffer buffer) {
    if (!buffer) unreachable();
    buffer->refCount--;
    if (buffer->refCount < 0) unreachable();
    if (buffer->refCount == 0) {
        if (buffer->mapping) {
            imports_list_u8_free(buffer->mapping);
        }
        wasi_webgpu_webgpu_gpu_buffer_drop_own(buffer->buffer);
        free(buffer);
    }
}

// void wgpuCommandBufferSetLabel(WGPUCommandBuffer commandBuffer, WGPUStringView label)
// {
// }

void wgpuCommandBufferAddRef(WGPUCommandBuffer commandBuffer) {
    if (!commandBuffer) unreachable();
    commandBuffer->refCount++;
}

void wgpuCommandBufferRelease(WGPUCommandBuffer commandBuffer) {
    if (!commandBuffer) unreachable();
    commandBuffer->refCount--;
    if (commandBuffer->refCount < 0) unreachable();
    if (commandBuffer->refCount == 0) {
        wasi_webgpu_webgpu_gpu_command_buffer_drop_own(commandBuffer->command_buffer);
        free(commandBuffer);
    }
}

WGPUComputePassEncoder
wgpuCommandEncoderBeginComputePass(WGPUCommandEncoder commandEncoder, WGPUComputePassDescriptor const* descriptor) {
    if (!commandEncoder) unreachable();

    wasi_webgpu_webgpu_gpu_compute_pass_descriptor_t descriptor_wasi = {};

    if (descriptor) {
        descriptor_wasi.label = labelNativeToWasi(&descriptor->label);
        if (descriptor->timestampWrites) {
            if (!descriptor->timestampWrites->querySet) unreachable();

            WGPUPassTimestampWrites const* writesNative = descriptor->timestampWrites;
            wasi_webgpu_webgpu_gpu_compute_pass_timestamp_writes_t* writes_wasi = &descriptor_wasi.timestamp_writes.val;

            descriptor_wasi.timestamp_writes.is_some = true;
            writes_wasi->query_set = wasi_webgpu_webgpu_borrow_gpu_query_set(writesNative->querySet->query_set);
            writes_wasi->beginning_of_pass_write_index.is_some =
                writesNative->beginningOfPassWriteIndex != WGPU_QUERY_SET_INDEX_UNDEFINED;
            if (writes_wasi->beginning_of_pass_write_index.is_some) {
                writes_wasi->beginning_of_pass_write_index.val = writesNative->beginningOfPassWriteIndex;
            }
            writes_wasi->end_of_pass_write_index.is_some =
                writesNative->endOfPassWriteIndex != WGPU_QUERY_SET_INDEX_UNDEFINED;
            if (writes_wasi->end_of_pass_write_index.is_some) {
                writes_wasi->end_of_pass_write_index.val = writesNative->endOfPassWriteIndex;
            }
        }
    };

    wasi_webgpu_webgpu_own_gpu_compute_pass_encoder_t compute_pass_encoder =
        wasi_webgpu_webgpu_method_gpu_command_encoder_begin_compute_pass(
            wasi_webgpu_webgpu_borrow_gpu_command_encoder(commandEncoder->command_encoder),
            descriptor ? &descriptor_wasi : NULL
        );

    wasi_webgpu_webgpu_gpu_compute_pass_descriptor_free(&descriptor_wasi);

    WGPUComputePassEncoderImpl* compute_pass_encoder_struct = malloc(sizeof(WGPUComputePassEncoderImpl));
    compute_pass_encoder_struct->compute_pass_encoder = compute_pass_encoder;
    compute_pass_encoder_struct->refCount = 1;
    return compute_pass_encoder_struct;
}

// WGPURenderPassEncoder wgpuCommandEncoderBeginRenderPass(WGPUCommandEncoder commandEncoder,
//     WGPURenderPassDescriptor const* descriptor)
// {
// }

// void wgpuCommandEncoderClearBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t
// size)
// {
// }

void wgpuCommandEncoderCopyBufferToBuffer(
    WGPUCommandEncoder commandEncoder,
    WGPUBuffer source,
    uint64_t sourceOffset,
    WGPUBuffer destination,
    uint64_t destinationOffset,
    uint64_t size
) {
    if (!commandEncoder || !source || !destination) unreachable();
    wasi_webgpu_webgpu_method_gpu_command_encoder_copy_buffer_to_buffer(
        wasi_webgpu_webgpu_borrow_gpu_command_encoder(commandEncoder->command_encoder),
        wasi_webgpu_webgpu_borrow_gpu_buffer(source->buffer),
        sourceOffset,
        wasi_webgpu_webgpu_borrow_gpu_buffer(destination->buffer),
        destinationOffset,
        size
    );
}

// void wgpuCommandEncoderCopyBufferToTexture(WGPUCommandEncoder commandEncoder, WGPUTexelCopyBufferInfo const* source,
//     WGPUTexelCopyTextureInfo const* destination, WGPUExtent3D const* copySize)
// {
// }

// void wgpuCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder commandEncoder, WGPUTexelCopyTextureInfo const* source,
//     WGPUTexelCopyBufferInfo const* destination, WGPUExtent3D const* copySize)
// {
// }

// void wgpuCommandEncoderCopyTextureToTexture(WGPUCommandEncoder commandEncoder, WGPUTexelCopyTextureInfo const*
// source,
//     WGPUTexelCopyTextureInfo const* destination, WGPUExtent3D const* copySize)
// {
// }

WGPUCommandBuffer
wgpuCommandEncoderFinish(WGPUCommandEncoder commandEncoder, WGPUCommandBufferDescriptor const* descriptor) {
    if (!commandEncoder) unreachable();

    wasi_webgpu_webgpu_gpu_command_buffer_descriptor_t descriptor_wasi = {
        .label = labelNativeToWasi(&descriptor->label),
    };

    wasi_webgpu_webgpu_borrow_gpu_command_encoder_t command_encoder_borrow =
        wasi_webgpu_webgpu_borrow_gpu_command_encoder(commandEncoder->command_encoder);
    wasi_webgpu_webgpu_own_gpu_command_buffer_t command_buffer_wasi =
        wasi_webgpu_webgpu_method_gpu_command_encoder_finish(command_encoder_borrow, &descriptor_wasi);

    wasi_webgpu_webgpu_gpu_command_buffer_descriptor_free(&descriptor_wasi);

    WGPUCommandBufferImpl* command_buffer_struct = malloc(sizeof(WGPUCommandBufferImpl));
    command_buffer_struct->command_buffer = command_buffer_wasi;
    command_buffer_struct->refCount = 1;
    return command_buffer_struct;
}

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

void wgpuCommandEncoderAddRef(WGPUCommandEncoder commandEncoder) {
    if (!commandEncoder) unreachable();
    commandEncoder->refCount++;
}

void wgpuCommandEncoderRelease(WGPUCommandEncoder commandEncoder) {
    if (!commandEncoder) unreachable();
    commandEncoder->refCount--;
    if (commandEncoder->refCount < 0) unreachable();
    if (commandEncoder->refCount == 0) {
        wasi_webgpu_webgpu_gpu_command_encoder_drop_own(commandEncoder->command_encoder);
        free(commandEncoder);
    }
}

void wgpuComputePassEncoderDispatchWorkgroups(
    WGPUComputePassEncoder computePassEncoder,
    uint32_t workgroupCountX,
    uint32_t workgroupCountY,
    uint32_t workgroupCountZ
) {
    if (!computePassEncoder) unreachable();
    wasi_webgpu_webgpu_method_gpu_compute_pass_encoder_dispatch_workgroups(
        wasi_webgpu_webgpu_borrow_gpu_compute_pass_encoder(computePassEncoder->compute_pass_encoder),
        workgroupCountX,
        &workgroupCountY,
        &workgroupCountZ
    );
}

// void wgpuComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder computePassEncoder,
//     WGPUBuffer indirectBuffer, uint64_t indirectOffset)
// {
// }

void wgpuComputePassEncoderEnd(WGPUComputePassEncoder computePassEncoder) {
    if (!computePassEncoder) unreachable();
    wasi_webgpu_webgpu_method_gpu_compute_pass_encoder_end(
        wasi_webgpu_webgpu_borrow_gpu_compute_pass_encoder(computePassEncoder->compute_pass_encoder)
    );
}

// void wgpuComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder computePassEncoder, WGPUStringView markerLabel)
// {
// }

// void wgpuComputePassEncoderPopDebugGroup(WGPUComputePassEncoder computePassEncoder)
// {
// }

// void wgpuComputePassEncoderPushDebugGroup(WGPUComputePassEncoder computePassEncoder, WGPUStringView groupLabel)
// {
// }

void wgpuComputePassEncoderSetBindGroup(
    WGPUComputePassEncoder computePassEncoder,
    uint32_t groupIndex,
    WGPUBindGroup group,
    size_t dynamicOffsetCount,
    uint32_t const* dynamicOffsets
) {
    if (!computePassEncoder) unreachable();

    wasi_webgpu_webgpu_set_bind_group_error_t err;

    wasi_webgpu_webgpu_borrow_gpu_bind_group_t group_borrow;
    wasi_webgpu_webgpu_borrow_gpu_bind_group_t* group_wasi = NULL;
    if (group) {
        group_borrow = wasi_webgpu_webgpu_borrow_gpu_bind_group(group->bind_group);
        group_wasi = &group_borrow;
    }

    imports_list_gpu_buffer_dynamic_offset_t offsets_data_val;
    imports_list_gpu_buffer_dynamic_offset_t* offsets_data_wasi = NULL;
    if (dynamicOffsetCount > 0) {
        offsets_data_val = (imports_list_gpu_buffer_dynamic_offset_t){
            .ptr = malloc(dynamicOffsetCount * sizeof(wasi_webgpu_webgpu_gpu_buffer_dynamic_offset_t)),
            .len = dynamicOffsetCount,
        };
        memcpy(
            offsets_data_val.ptr,
            dynamicOffsets,
            dynamicOffsetCount * sizeof(wasi_webgpu_webgpu_gpu_buffer_dynamic_offset_t)
        );

        offsets_data_wasi = &offsets_data_val;
    }

    bool success = wasi_webgpu_webgpu_method_gpu_compute_pass_encoder_set_bind_group(
        wasi_webgpu_webgpu_borrow_gpu_compute_pass_encoder(computePassEncoder->compute_pass_encoder),
        groupIndex,
        group_wasi,
        offsets_data_wasi,
        NULL, // No offsets offset in webgpu.h
        NULL, // length already handled in group_wasi.val.len
        &err
    );
    if (!success) {
        wasi_webgpu_webgpu_set_bind_group_error_free(&err);
        todo();
    }
    if (dynamicOffsetCount > 0) {
        free(offsets_data_wasi->ptr);
    }
}

// void wgpuComputePassEncoderSetLabel(WGPUComputePassEncoder computePassEncoder, WGPUStringView label)
// {
// }

void wgpuComputePassEncoderSetPipeline(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline) {
    if (!computePassEncoder) unreachable();
    wasi_webgpu_webgpu_method_gpu_compute_pass_encoder_set_pipeline(
        wasi_webgpu_webgpu_borrow_gpu_compute_pass_encoder(computePassEncoder->compute_pass_encoder),
        wasi_webgpu_webgpu_borrow_gpu_compute_pipeline(pipeline->compute_pipeline)
    );
}

void wgpuComputePassEncoderAddRef(WGPUComputePassEncoder computePassEncoder) {
    if (!computePassEncoder) unreachable();
    computePassEncoder->refCount++;
}

void wgpuComputePassEncoderRelease(WGPUComputePassEncoder computePassEncoder) {
    if (!computePassEncoder) unreachable();
    computePassEncoder->refCount--;
    if (computePassEncoder->refCount < 0) unreachable();
    if (computePassEncoder->refCount == 0) {
        wasi_webgpu_webgpu_gpu_compute_pass_encoder_drop_own(computePassEncoder->compute_pass_encoder);
        free(computePassEncoder);
    }
}

WGPUBindGroupLayout wgpuComputePipelineGetBindGroupLayout(WGPUComputePipeline computePipeline, uint32_t groupIndex) {
    if (!computePipeline) unreachable();

    wasi_webgpu_webgpu_own_gpu_bind_group_layout_t bind_group_layout =
        wasi_webgpu_webgpu_method_gpu_compute_pipeline_get_bind_group_layout(
            wasi_webgpu_webgpu_borrow_gpu_compute_pipeline(computePipeline->compute_pipeline),
            groupIndex
        );
    WGPUBindGroupLayoutImpl* bind_group_layout_struct = malloc(sizeof(WGPUBindGroupLayoutImpl));
    bind_group_layout_struct->bind_group_layout = bind_group_layout;
    bind_group_layout_struct->refCount = 1;
    return (WGPUBindGroupLayout)bind_group_layout_struct;
}

// void wgpuComputePipelineSetLabel(WGPUComputePipeline computePipeline, WGPUStringView label)
// {
// }

void wgpuComputePipelineAddRef(WGPUComputePipeline computePipeline) {
    if (!computePipeline) unreachable();
    computePipeline->refCount++;
}

void wgpuComputePipelineRelease(WGPUComputePipeline computePipeline) {
    if (!computePipeline) unreachable();
    computePipeline->refCount--;
    if (computePipeline->refCount < 0) unreachable();
    if (computePipeline->refCount == 0) {
        wasi_webgpu_webgpu_gpu_compute_pipeline_drop_own(computePipeline->compute_pipeline);
        free(computePipeline);
    }
}

WGPUBindGroup wgpuDeviceCreateBindGroup(WGPUDevice device, WGPUBindGroupDescriptor const* descriptor) {
    if (!device || !descriptor || !descriptor->entries) unreachable();

    wasi_webgpu_webgpu_gpu_bind_group_entry_t* entries_array =
        malloc(descriptor->entryCount * sizeof(wasi_webgpu_webgpu_gpu_bind_group_entry_t));

    for (size_t i = 0; i < descriptor->entryCount; i++) {
        wasi_webgpu_webgpu_gpu_binding_resource_t resource = {};
        if (descriptor->entries[i].buffer) {
            resource.tag = WASI_WEBGPU_WEBGPU_GPU_BINDING_RESOURCE_GPU_BUFFER_BINDING;
            resource.val.gpu_buffer_binding = (wasi_webgpu_webgpu_gpu_buffer_binding_t){
                .buffer = wasi_webgpu_webgpu_borrow_gpu_buffer(descriptor->entries[i].buffer->buffer),
                .offset =
                    (imports_option_gpu_size64_t){
                        .is_some = true,
                        .val = descriptor->entries[i].offset,
                    },
                .size = (imports_option_gpu_size64_t){
                    .is_some = true,
                    .val = descriptor->entries[i].size,
                },
            };
        } else if (descriptor->entries[i].sampler) {
            resource.tag = WASI_WEBGPU_WEBGPU_GPU_BINDING_RESOURCE_GPU_SAMPLER;
            todo();
        } else if (descriptor->entries[i].textureView) {
            resource.tag = WASI_WEBGPU_WEBGPU_GPU_BINDING_RESOURCE_GPU_TEXTURE_VIEW;
            todo();
        } else {
            unreachable();
        }

        entries_array[i] = (wasi_webgpu_webgpu_gpu_bind_group_entry_t){
            .binding = descriptor->entries[i].binding,
            .resource = resource,
        };
    }

    wasi_webgpu_webgpu_gpu_bind_group_descriptor_t descriptor_wasi = {
        .layout = wasi_webgpu_webgpu_borrow_gpu_bind_group_layout(descriptor->layout->bind_group_layout),
        .label = labelNativeToWasi(&descriptor->label),
        .entries = (wasi_webgpu_webgpu_list_gpu_bind_group_entry_t){
            .ptr = entries_array,
            .len = descriptor->entryCount,
        },
    };

    wasi_webgpu_webgpu_own_gpu_bind_group_t bind_group = wasi_webgpu_webgpu_method_gpu_device_create_bind_group(
        wasi_webgpu_webgpu_borrow_gpu_device(device->device),
        &descriptor_wasi
    );

    wasi_webgpu_webgpu_gpu_bind_group_descriptor_free(&descriptor_wasi);

    WGPUBindGroupImpl* bind_group_struct = malloc(sizeof(WGPUBindGroupImpl));
    bind_group_struct->bind_group = bind_group;
    bind_group_struct->refCount = 1;
    return bind_group_struct;
}

// WGPUBindGroupLayout wgpuDeviceCreateBindGroupLayout(WGPUDevice device, WGPUBindGroupLayoutDescriptor const*
// descriptor)
// {
// }

WGPUBuffer wgpuDeviceCreateBuffer(WGPUDevice device, WGPUBufferDescriptor const* descriptor) {
    if (!device) unreachable();

    wasi_webgpu_webgpu_gpu_buffer_descriptor_t descriptor_wasi = {};

    if (descriptor) {
        descriptor_wasi.size = descriptor->size;
        descriptor_wasi.usage = descriptor->usage;
        descriptor_wasi.label = labelNativeToWasi(&descriptor->label);
        descriptor_wasi.mapped_at_creation = (imports_option_bool_t){
            .is_some = true,
            .val = descriptor->mappedAtCreation,
        };
    }

    wasi_webgpu_webgpu_own_gpu_buffer_t buffer = wasi_webgpu_webgpu_method_gpu_device_create_buffer(
        wasi_webgpu_webgpu_borrow_gpu_device(device->device),
        &descriptor_wasi
    );

    wasi_webgpu_webgpu_gpu_buffer_descriptor_free(&descriptor_wasi);

    WGPUBufferImpl* buffer_struct = malloc(sizeof(WGPUBufferImpl));
    buffer_struct->buffer = buffer;
    buffer_struct->refCount = 1;
    buffer_struct->mapping = NULL;
    return (WGPUBuffer)buffer_struct;
}

WGPUCommandEncoder wgpuDeviceCreateCommandEncoder(WGPUDevice device, WGPUCommandEncoderDescriptor const* descriptor) {
    if (!device) unreachable();

    wasi_webgpu_webgpu_gpu_command_encoder_descriptor_t descriptor_wasi = {};
    if (descriptor) {
        descriptor_wasi.label = labelNativeToWasi(&descriptor->label);
    }
    wasi_webgpu_webgpu_own_gpu_command_encoder_t command_encoder =
        wasi_webgpu_webgpu_method_gpu_device_create_command_encoder(
            wasi_webgpu_webgpu_borrow_gpu_device(device->device),
            &descriptor_wasi
        );

    wasi_webgpu_webgpu_gpu_command_encoder_descriptor_free(&descriptor_wasi);

    WGPUCommandEncoderImpl* command_encoder_struct = malloc(sizeof(WGPUCommandEncoderImpl));
    command_encoder_struct->command_encoder = command_encoder;
    command_encoder_struct->refCount = 1;
    return command_encoder_struct;
}

WGPUComputePipeline
wgpuDeviceCreateComputePipeline(WGPUDevice device, WGPUComputePipelineDescriptor const* descriptor) {
    if (!device || !descriptor) unreachable();

    wasi_webgpu_webgpu_gpu_layout_mode_t layout_wasi = {};
    if (!descriptor->layout) {
        layout_wasi.tag = WASI_WEBGPU_WEBGPU_GPU_LAYOUT_MODE_AUTO;
    } else {
        layout_wasi.tag = WASI_WEBGPU_WEBGPU_GPU_LAYOUT_MODE_SPECIFIC;
        layout_wasi.val.specific = wasi_webgpu_webgpu_borrow_gpu_pipeline_layout(descriptor->layout->pipeline_layout);
    }

    imports_option_string_t entry_point_wasi = {};
    entry_point_wasi.is_some = descriptor->compute.entryPoint.data != NULL;
    if (entry_point_wasi.is_some) {
        entry_point_wasi.val = (imports_string_t){.ptr = malloc(descriptor->compute.entryPoint.length),
                                                  .len = descriptor->compute.entryPoint.length};
        memcpy(entry_point_wasi.val.ptr, descriptor->compute.entryPoint.data, descriptor->compute.entryPoint.length);
    }

    wasi_webgpu_webgpu_option_own_record_gpu_pipeline_constant_value_t constants_wasi = {};
    constants_wasi.is_some = descriptor->compute.constantCount > 0;
    if (constants_wasi.is_some) {
        if (!descriptor->compute.constants) unreachable();

        constants_wasi.val = wasi_webgpu_webgpu_constructor_record_gpu_pipeline_constant_value();
        for (size_t i = 0; i < descriptor->compute.constantCount; i++) {
            imports_string_t key = {};
            key.ptr = malloc(descriptor->compute.constants[i].key.length);
            key.len = descriptor->compute.constants[i].key.length;
            memcpy(key.ptr, descriptor->compute.constants[i].key.data, descriptor->compute.constants[i].key.length);

            wasi_webgpu_webgpu_method_record_gpu_pipeline_constant_value_add(
                wasi_webgpu_webgpu_borrow_record_gpu_pipeline_constant_value(constants_wasi.val),
                &key,
                descriptor->compute.constants[i].value
            );
        }
    }

    wasi_webgpu_webgpu_gpu_compute_pipeline_descriptor_t descriptor_wasi = {
        .label = labelNativeToWasi(&descriptor->label),
        .layout = layout_wasi,
        .compute = (wasi_webgpu_webgpu_gpu_programmable_stage_t){
            .module = wasi_webgpu_webgpu_borrow_gpu_shader_module(descriptor->compute.module->module),
            .entry_point = entry_point_wasi,
            .constants = constants_wasi,
        },
    };

    wasi_webgpu_webgpu_own_gpu_compute_pipeline_t compute_pipeline =
        wasi_webgpu_webgpu_method_gpu_device_create_compute_pipeline(
            wasi_webgpu_webgpu_borrow_gpu_device(device->device),
            &descriptor_wasi
        );

    wasi_webgpu_webgpu_gpu_compute_pipeline_descriptor_free(&descriptor_wasi);

    WGPUComputePipelineImpl* compute_pipeline_struct = malloc(sizeof(WGPUComputePipelineImpl));
    compute_pipeline_struct->compute_pipeline = compute_pipeline;
    compute_pipeline_struct->refCount = 1;
    return (WGPUComputePipeline)compute_pipeline_struct;
}

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

WGPUShaderModule wgpuDeviceCreateShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const* descriptor) {
    if (!device || !descriptor || !descriptor->nextInChain) unreachable();

    WGPUShaderSourceWGSL* wgsl_source = NULL;
    switch (descriptor->nextInChain->sType) {
    case WGPUSType_ShaderSourceWGSL:
        wgsl_source = (WGPUShaderSourceWGSL*)descriptor->nextInChain;
        break;
    case WGPUSType_ShaderSourceSPIRV:
        // consider adding SPIRV support
        todo();
        break;
    default:
        unreachable();
    }

    imports_string_t code_wasi = {
        .ptr = malloc(wgsl_source->code.length),
        .len = wgsl_source->code.length,
    };
    memcpy(code_wasi.ptr, wgsl_source->code.data, wgsl_source->code.length);

    wasi_webgpu_webgpu_gpu_shader_module_descriptor_t descriptor_wasi = {
        .code = code_wasi,
        .label = labelNativeToWasi(&descriptor->label),
        .compilation_hints = (wasi_webgpu_webgpu_option_list_gpu_shader_module_compilation_hint_t){
            // webgpu.h doesn't have compilation hints yet
            .is_some = false,
        },
    };

    wasi_webgpu_webgpu_own_gpu_shader_module_t shader_module =
        wasi_webgpu_webgpu_method_gpu_device_create_shader_module(
            wasi_webgpu_webgpu_borrow_gpu_device(device->device),
            &descriptor_wasi
        );

    wasi_webgpu_webgpu_gpu_shader_module_descriptor_free(&descriptor_wasi);

    WGPUShaderModuleImpl* shader_module_struct = malloc(sizeof(WGPUShaderModuleImpl));
    shader_module_struct->module = shader_module;
    shader_module_struct->refCount = 1;
    return shader_module_struct;
}

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

WGPUQueue wgpuDeviceGetQueue(WGPUDevice device) {
    if (!device) unreachable();
    wasi_webgpu_webgpu_own_gpu_queue_t queue =
        wasi_webgpu_webgpu_method_gpu_device_queue(wasi_webgpu_webgpu_borrow_gpu_device(device->device));

    WGPUQueueImpl* queue_struct = malloc(sizeof(WGPUQueueImpl));
    queue_struct->queue = queue;
    queue_struct->refCount = 1;
    return queue_struct;
}

WGPUBool wgpuDeviceHasFeature(WGPUDevice device, WGPUFeatureName feature) {
    imports_string_t feature_wasi_string = featureNativeToWasiString(feature);
    wasi_webgpu_webgpu_own_gpu_supported_features_t available_features =
        wasi_webgpu_webgpu_method_gpu_device_features(wasi_webgpu_webgpu_borrow_gpu_device(device->device));
    return wasi_webgpu_webgpu_method_gpu_supported_features_has(
        wasi_webgpu_webgpu_borrow_gpu_supported_features(available_features),
        &feature_wasi_string
    );
}

// WGPUFuture wgpuDevicePopErrorScope(WGPUDevice device, WGPUPopErrorScopeCallbackInfo callbackInfo)
// {
// }

// void wgpuDevicePushErrorScope(WGPUDevice device, WGPUErrorFilter filter)
// {
// }

// void wgpuDeviceSetLabel(WGPUDevice device, WGPUStringView label)
// {
// }

void wgpuDeviceAddRef(WGPUDevice device) {
    if (!device) unreachable();
    device->refCount++;
}

void wgpuDeviceRelease(WGPUDevice device) {
    if (!device) unreachable();
    device->refCount--;
    if (device->refCount < 0) unreachable();
    if (device->refCount == 0) {
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

WGPUFuture wgpuInstanceRequestAdapter(
    WGPUInstance instance,
    WGPURequestAdapterOptions const* options,
    WGPURequestAdapterCallbackInfo callbackInfo
) {
    if (!instance) unreachable();

    wasi_webgpu_webgpu_gpu_request_adapter_options_t wasi_options = {};
    if (options) {
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

    if (!success) {
        todo();
    }

    WGPUAdapterImpl* adapter = malloc(sizeof(WGPUAdapterImpl));
    adapter->refCount = 1;
    adapter->adapter = wasi_adapter;

    wasi_webgpu_webgpu_gpu_request_adapter_options_free(&wasi_options);

    callbackInfo.callback(
        WGPURequestAdapterStatus_Success,
        adapter,
        WGPU_STRING_VIEW_INIT,
        callbackInfo.userdata1,
        callbackInfo.userdata2
    );
    return (WGPUFuture){.id = 0};
}

WGPUWaitStatus
wgpuInstanceWaitAny(WGPUInstance instance, size_t futureCount, WGPUFutureWaitInfo* futures, uint64_t timeoutNS) {
    // TODO: implement futures
    // For now, the returning function is just calling the callback immediately
    return WGPUWaitStatus_Success;
}

void wgpuInstanceAddRef(WGPUInstance instance) {
    if (!instance) unreachable();
    instance->refCount++;
}

void wgpuInstanceRelease(WGPUInstance instance) {
    if (!instance) unreachable();
    instance->refCount--;
    if (instance->refCount < 0) unreachable();
    if (instance->refCount == 0) {
        wasi_webgpu_webgpu_gpu_drop_own(instance->gpu);
        free(instance);
    }
}

// void wgpuPipelineLayoutSetLabel(WGPUPipelineLayout pipelineLayout, WGPUStringView label)
// {
// }

void wgpuPipelineLayoutAddRef(WGPUPipelineLayout pipelineLayout) {
    if (!pipelineLayout) unreachable();
    pipelineLayout->refCount++;
}

void wgpuPipelineLayoutRelease(WGPUPipelineLayout pipelineLayout) {
    if (!pipelineLayout) unreachable();
    pipelineLayout->refCount--;
    if (pipelineLayout->refCount < 0) unreachable();
    if (pipelineLayout->refCount == 0) {
        wasi_webgpu_webgpu_gpu_pipeline_layout_drop_own(pipelineLayout->pipeline_layout);
        free(pipelineLayout);
    }
}

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

void wgpuQuerySetAddRef(WGPUQuerySet querySet) {
    if (!querySet) unreachable();
    querySet->refCount++;
}

void wgpuQuerySetRelease(WGPUQuerySet querySet) {
    if (!querySet) unreachable();
    querySet->refCount--;
    if (querySet->refCount < 0) unreachable();
    if (querySet->refCount == 0) {
        wasi_webgpu_webgpu_gpu_query_set_drop_own(querySet->query_set);
        free(querySet);
    }
}

// WGPUFuture wgpuQueueOnSubmittedWorkDone(WGPUQueue queue, WGPUQueueWorkDoneCallbackInfo callbackInfo)
// {
// }

// void wgpuQueueSetLabel(WGPUQueue queue, WGPUStringView label)
// {
// }

void wgpuQueueSubmit(WGPUQueue queue, size_t commandCount, WGPUCommandBuffer const* commands) {
    if (!queue) unreachable();
    wasi_webgpu_webgpu_list_borrow_gpu_command_buffer_t commands_wasi = {
        .ptr = malloc(sizeof(wasi_webgpu_webgpu_borrow_gpu_command_buffer_t) * commandCount),
        .len = commandCount
    };
    for (size_t i = 0; i < commandCount; i++) {
        commands_wasi.ptr[i] = wasi_webgpu_webgpu_borrow_gpu_command_buffer(commands[i]->command_buffer);
    }
    wasi_webgpu_webgpu_method_gpu_queue_submit(wasi_webgpu_webgpu_borrow_gpu_queue(queue->queue), &commands_wasi);

    wasi_webgpu_webgpu_list_borrow_gpu_command_buffer_free(&commands_wasi);
}

void wgpuQueueWriteBuffer(WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const* data, size_t size) {
    if (!queue || !buffer || !data) unreachable();

    imports_list_u8_t data_wasi = {
        .ptr = (uint8_t*)data,
        .len = size,
    };

    wasi_webgpu_webgpu_write_buffer_error_t err;
    bool success = wasi_webgpu_webgpu_method_gpu_queue_write_buffer_with_copy(
        wasi_webgpu_webgpu_borrow_gpu_queue(queue->queue),
        wasi_webgpu_webgpu_borrow_gpu_buffer(buffer->buffer),
        bufferOffset,
        &data_wasi,
        NULL, // no data-offset in webgpu.h
        NULL, // no data-size in webgpu.h
        &err
    );
    if (!success) {
        wasi_webgpu_webgpu_write_buffer_error_free(&err);
        todo();
    }
}

// void wgpuQueueWriteTexture(WGPUQueue queue, WGPUTexelCopyTextureInfo const* destination, void const* data, size_t
// dataSize,
//     WGPUTexelCopyBufferLayout const* dataLayout, WGPUExtent3D const* writeSize)
// {
// }

void wgpuQueueAddRef(WGPUQueue queue) {
    if (!queue) unreachable();
    queue->refCount++;
}

void wgpuQueueRelease(WGPUQueue queue) {
    if (!queue) unreachable();
    queue->refCount--;
    if (queue->refCount < 0) unreachable();
    if (queue->refCount == 0) {
        wasi_webgpu_webgpu_gpu_queue_drop_own(queue->queue);
        free(queue);
    }
}

// void wgpuRenderBundleSetLabel(WGPURenderBundle renderBundle, WGPUStringView label)
// {
// }

void wgpuRenderBundleAddRef(WGPURenderBundle renderBundle) {
    if (!renderBundle) unreachable();
    renderBundle->refCount++;
}

void wgpuRenderBundleRelease(WGPURenderBundle renderBundle) {
    if (!renderBundle) unreachable();
    renderBundle->refCount--;
    if (renderBundle->refCount < 0) unreachable();
    if (renderBundle->refCount == 0) {
        wasi_webgpu_webgpu_gpu_render_bundle_drop_own(renderBundle->render_bundle);
        free(renderBundle);
    }
}

// void wgpuRenderBundleEncoderDraw(WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount,
//     uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
// {
// }

// void wgpuRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount,
//     uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance)
// {
// }

// void wgpuRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer
// indirectBuffer,
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

// void wgpuRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView
// markerLabel)
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

void wgpuRenderBundleEncoderAddRef(WGPURenderBundleEncoder renderBundleEncoder) {
    if (!renderBundleEncoder) unreachable();
    renderBundleEncoder->refCount++;
}

void wgpuRenderBundleEncoderRelease(WGPURenderBundleEncoder renderBundleEncoder) {
    if (!renderBundleEncoder) unreachable();
    renderBundleEncoder->refCount--;
    if (renderBundleEncoder->refCount < 0) unreachable();
    if (renderBundleEncoder->refCount == 0) {
        wasi_webgpu_webgpu_gpu_render_bundle_encoder_drop_own(renderBundleEncoder->render_bundle_encoder);
        free(renderBundleEncoder);
    }
}

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

void wgpuRenderPassEncoderAddRef(WGPURenderPassEncoder renderPassEncoder) {
    if (!renderPassEncoder) unreachable();
    renderPassEncoder->refCount++;
}

void wgpuRenderPassEncoderRelease(WGPURenderPassEncoder renderPassEncoder) {
    if (!renderPassEncoder) unreachable();
    renderPassEncoder->refCount--;
    if (renderPassEncoder->refCount < 0) unreachable();
    if (renderPassEncoder->refCount == 0) {
        wasi_webgpu_webgpu_gpu_render_pass_encoder_drop_own(renderPassEncoder->render_pass_encoder);
        free(renderPassEncoder);
    }
}

// WGPUBindGroupLayout wgpuRenderPipelineGetBindGroupLayout(WGPURenderPipeline renderPipeline, uint32_t groupIndex)
// {
// }

// void wgpuRenderPipelineSetLabel(WGPURenderPipeline renderPipeline, WGPUStringView label)
// {
// }

void wgpuRenderPipelineAddRef(WGPURenderPipeline renderPipeline) {
    if (!renderPipeline) unreachable();
    renderPipeline->refCount++;
}

void wgpuRenderPipelineRelease(WGPURenderPipeline renderPipeline) {
    if (!renderPipeline) unreachable();
    renderPipeline->refCount--;
    if (renderPipeline->refCount < 0) unreachable();
    if (renderPipeline->refCount == 0) {
        wasi_webgpu_webgpu_gpu_render_pipeline_drop_own(renderPipeline->render_pipeline);
        free(renderPipeline);
    }
}

// void wgpuSamplerSetLabel(WGPUSampler sampler, WGPUStringView label)
// {
// }

void wgpuSamplerAddRef(WGPUSampler sampler) {
    if (!sampler) unreachable();
    sampler->refCount++;
}

void wgpuSamplerRelease(WGPUSampler sampler) {
    if (!sampler) unreachable();
    sampler->refCount--;
    if (sampler->refCount < 0) unreachable();
    if (sampler->refCount == 0) {
        wasi_webgpu_webgpu_gpu_sampler_drop_own(sampler->sampler);
        free(sampler);
    }
}

// WGPUFuture wgpuShaderModuleGetCompilationInfo(WGPUShaderModule shaderModule,
//     WGPUCompilationInfoCallbackInfo callbackInfo)
// {
// }

// void wgpuShaderModuleSetLabel(WGPUShaderModule shaderModule, WGPUStringView label)
// {
// }

void wgpuShaderModuleAddRef(WGPUShaderModule shaderModule) {
    if (!shaderModule) unreachable();
    shaderModule->refCount++;
}

void wgpuShaderModuleRelease(WGPUShaderModule shaderModule) {
    if (!shaderModule) unreachable();
    shaderModule->refCount--;
    if (shaderModule->refCount < 0) unreachable();
    if (shaderModule->refCount == 0) {
        wasi_webgpu_webgpu_gpu_shader_module_drop_own(shaderModule->module);
        free(shaderModule);
    }
}

// void wgpuSupportedFeaturesFreeMembers(WGPUSupportedFeatures supportedFeatures)
// {
// }

// void wgpuSupportedWGSLLanguageFeaturesFreeMembers(WGPUSupportedWGSLLanguageFeatures supportedWGSLLanguageFeatures)
// {
// }

// void wgpuSurfaceConfigure(WGPUSurface surface, WGPUSurfaceConfiguration const* config)
// {
// }

// WGPUStatus wgpuSurfaceGetCapabilities(WGPUSurface surface, WGPUAdapter adapter, WGPUSurfaceCapabilities*
// capabilities)
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

void wgpuTextureAddRef(WGPUTexture texture) {
    if (!texture) unreachable();
    texture->refCount++;
}

void wgpuTextureRelease(WGPUTexture texture) {
    if (!texture) unreachable();
    texture->refCount--;
    if (texture->refCount < 0) unreachable();
    if (texture->refCount == 0) {
        wasi_webgpu_webgpu_gpu_texture_drop_own(texture->texture);
        free(texture);
    }
}

// void wgpuTextureViewSetLabel(WGPUTextureView textureView, WGPUStringView label)
// {
// }

void wgpuTextureViewAddRef(WGPUTextureView textureView) {
    if (!textureView) unreachable();
    textureView->refCount++;
}

void wgpuTextureViewRelease(WGPUTextureView textureView) {
    if (!textureView) unreachable();
    textureView->refCount--;
    if (textureView->refCount < 0) unreachable();
    if (textureView->refCount == 0) {
        wasi_webgpu_webgpu_gpu_texture_view_drop_own(textureView->texture_view);
        free(textureView);
    }
}

imports_option_string_t labelNativeToWasi(WGPUStringView const* label) {
    imports_option_string_t output = {};
    if (!label || !label->data) return output;

    output.is_some = true;
    output.val.ptr = malloc(label->length + 1);
    memcpy(output.val.ptr, label->data, label->length + 1);
    output.val.len = label->length;

    return output;
}

wasi_webgpu_webgpu_gpu_buffer_map_state_t bufferMapStateNativeToWasi(WGPUBufferMapState const bufferMapState) {
    switch (bufferMapState) {
    case WGPUBufferMapState_Unmapped:
        return WASI_WEBGPU_WEBGPU_GPU_BUFFER_MAP_STATE_UNMAPPED;
    case WGPUBufferMapState_Pending:
        return WASI_WEBGPU_WEBGPU_GPU_BUFFER_MAP_STATE_PENDING;
    case WGPUBufferMapState_Mapped:
        return WASI_WEBGPU_WEBGPU_GPU_BUFFER_MAP_STATE_MAPPED;
    default:
        unreachable();
    }
}

WGPUBufferMapState bufferMapStateWasiToNative(wasi_webgpu_webgpu_gpu_buffer_map_state_t const buffer_map_state) {
    switch (buffer_map_state) {
    case WASI_WEBGPU_WEBGPU_GPU_BUFFER_MAP_STATE_UNMAPPED:
        return WGPUBufferMapState_Unmapped;
    case WASI_WEBGPU_WEBGPU_GPU_BUFFER_MAP_STATE_PENDING:
        return WGPUBufferMapState_Pending;
    case WASI_WEBGPU_WEBGPU_GPU_BUFFER_MAP_STATE_MAPPED:
        return WGPUBufferMapState_Mapped;
    default:
        unreachable();
    }
}

imports_option_string_t featureLevelNativeToWasi(WGPUFeatureLevel featureLevel) {
    const char* compatibility = "compatibility";
    const char* core = "core";

    imports_option_string_t output = {};
    if (featureLevel == WGPUFeatureLevel_Undefined) {
        return output;
    }

    output.is_some = true;
    switch (featureLevel) {
    case WGPUFeatureLevel_Compatibility:
        output.val.ptr = malloc(strlen(compatibility) + 1);
        memcpy(output.val.ptr, compatibility, strlen(compatibility) + 1);
        output.val.len = strlen(compatibility);
        break;
    case WGPUFeatureLevel_Core:
        output.val.ptr = malloc(strlen(core) + 1);
        memcpy(output.val.ptr, core, strlen(core) + 1);
        output.val.len = strlen(core);
        break;
    default:
        unreachable();
    }
    return output;
}

wasi_webgpu_webgpu_option_gpu_power_preference_t powerPreferenceNativeToWasi(WGPUPowerPreference powerPreference) {
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

wasi_webgpu_webgpu_gpu_feature_name_t featureNativeToWasi(WGPUFeatureName const feature) {
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

// needed while feature checking is done with strings
// spec might change https://github.com/WebAssembly/wasi-gfx/issues/58
imports_string_t featureNativeToWasiString(WGPUFeatureName const feature) {
    const char* depth_clip_control = "depth-clip-control";
    const char* depth32float_stencil8 = "depth32float-stencil8";
    const char* texture_compression_bc = "texture-compression-bc";
    const char* texture_compression_bc_sliced3d = "texture-compression-bc-sliced3d";
    const char* texture_compression_etc2 = "texture-compression-etc2";
    const char* texture_compression_astc = "texture-compression-astc";
    const char* texture_compression_astc_sliced3d = "texture-compression-astc-sliced3d";
    const char* timestamp_query = "timestamp-query";
    const char* indirect_first_instance = "indirect-first-instance";
    const char* shader_f16 = "shader-f16";
    const char* rg11b10ufloat_renderable = "rg11b10ufloat-renderable";
    const char* bgra8unorm_storage = "bgra8unorm-storage";
    const char* float32_filterable = "float32-filterable";
    const char* float32_blendable = "float32-blendable";
    const char* clip_distances = "clip-distances";
    const char* dual_source_blending = "dual-source-blending";
    const char* subgroups = "subgroups";

    const char* c_string = NULL;

    switch (feature) {
    case WGPUFeatureName_DepthClipControl:
        c_string = depth_clip_control;
        break;
    case WGPUFeatureName_Depth32FloatStencil8:
        c_string = depth32float_stencil8;
        break;
    case WGPUFeatureName_TextureCompressionBC:
        c_string = texture_compression_bc;
        break;
    case WGPUFeatureName_TextureCompressionBCSliced3D:
        c_string = texture_compression_bc_sliced3d;
        break;
    case WGPUFeatureName_TextureCompressionETC2:
        c_string = texture_compression_etc2;
        break;
    case WGPUFeatureName_TextureCompressionASTC:
        c_string = texture_compression_astc;
        break;
    case WGPUFeatureName_TextureCompressionASTCSliced3D:
        c_string = texture_compression_astc_sliced3d;
        break;
    case WGPUFeatureName_TimestampQuery:
        c_string = timestamp_query;
        break;
    case WGPUFeatureName_IndirectFirstInstance:
        c_string = indirect_first_instance;
        break;
    case WGPUFeatureName_ShaderF16:
        c_string = shader_f16;
        break;
    case WGPUFeatureName_RG11B10UfloatRenderable:
        c_string = rg11b10ufloat_renderable;
        break;
    case WGPUFeatureName_BGRA8UnormStorage:
        c_string = bgra8unorm_storage;
        break;
    case WGPUFeatureName_Float32Filterable:
        c_string = float32_filterable;
        break;
    case WGPUFeatureName_Float32Blendable:
        c_string = float32_blendable;
        break;
    case WGPUFeatureName_ClipDistances:
        c_string = clip_distances;
        break;
    case WGPUFeatureName_DualSourceBlending:
        c_string = dual_source_blending;
        break;
    case WGPUFeatureName_Subgroups:
        c_string = subgroups;
        break;
    default:
        unreachable();
    }

    imports_string_t output = {};
    size_t len = strlen(c_string);
    output.ptr = malloc(len);
    memcpy(output.ptr, c_string, len);
    output.len = len;
    return output;
}

WGPUFeatureName featureWasiToNative(wasi_webgpu_webgpu_gpu_feature_name_t const feature) {
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

wasi_webgpu_webgpu_option_own_record_option_gpu_size64_t limitsNativeToWasi(WGPULimits const* limits_native) {
#define ADD_LIMIT_U32(field, name)                                                                                     \
    if (limits_native->field != WGPU_LIMIT_U32_UNDEFINED) {                                                            \
        imports_string_t str = {.ptr = (uint8_t*)name, .len = strlen(name)};                                           \
        uint64_t val = (uint64_t)limits_native->field;                                                                 \
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(limits_wasi_borrow, &str, &val);                        \
    }
#define ADD_LIMIT_U64(field, name)                                                                                     \
    if (limits_native->field != WGPU_LIMIT_U64_UNDEFINED) {                                                            \
        imports_string_t str = {.ptr = (uint8_t*)name, .len = strlen(name)};                                           \
        uint64_t val = (uint64_t)limits_native->field;                                                                 \
        wasi_webgpu_webgpu_method_record_option_gpu_size64_add(limits_wasi_borrow, &str, &val);                        \
    }

    wasi_webgpu_webgpu_option_own_record_option_gpu_size64_t output = {};
    if (!limits_native) {
        return output;
    }

    output.is_some = true;
    output.val = wasi_webgpu_webgpu_constructor_record_option_gpu_size64();
    wasi_webgpu_webgpu_borrow_record_option_gpu_size64_t limits_wasi_borrow =
        wasi_webgpu_webgpu_borrow_record_option_gpu_size64(output.val);

    ADD_LIMIT_U32(maxTextureDimension1D, "max-texture-dimension1-d");
    ADD_LIMIT_U32(maxTextureDimension2D, "max-texture-dimension2-d");
    ADD_LIMIT_U32(maxTextureDimension3D, "max-texture-dimension3-d");
    ADD_LIMIT_U32(maxTextureArrayLayers, "max-texture-array-layers");
    ADD_LIMIT_U32(maxBindGroups, "max-bind-groups");
    ADD_LIMIT_U32(maxBindGroupsPlusVertexBuffers, "max-bind-groups-plus-vertex-buffers");
    ADD_LIMIT_U32(maxBindingsPerBindGroup, "max-bindings-per-bind-group");
    ADD_LIMIT_U32(maxDynamicUniformBuffersPerPipelineLayout, "max-dynamic-uniform-buffers-per-pipeline-layout");
    ADD_LIMIT_U32(maxDynamicStorageBuffersPerPipelineLayout, "max-dynamic-storage-buffers-per-pipeline-layout");
    ADD_LIMIT_U32(maxSampledTexturesPerShaderStage, "max-sampled-textures-per-shader-stage");
    ADD_LIMIT_U32(maxSamplersPerShaderStage, "max-samplers-per-shader-stage");
    ADD_LIMIT_U32(maxStorageBuffersPerShaderStage, "max-storage-buffers-per-shader-stage");
    ADD_LIMIT_U32(maxStorageTexturesPerShaderStage, "max-storage-textures-per-shader-stage");
    ADD_LIMIT_U32(maxUniformBuffersPerShaderStage, "max-uniform-buffers-per-shader-stage");
    ADD_LIMIT_U64(maxUniformBufferBindingSize, "max-uniform-buffer-binding-size");
    ADD_LIMIT_U64(maxStorageBufferBindingSize, "max-storage-buffer-binding-size");
    ADD_LIMIT_U32(minUniformBufferOffsetAlignment, "min-uniform-buffer-offset-alignment");
    ADD_LIMIT_U32(minStorageBufferOffsetAlignment, "min-storage-buffer-offset-alignment");
    ADD_LIMIT_U32(maxVertexBuffers, "max-vertex-buffers");
    ADD_LIMIT_U64(maxBufferSize, "max-buffer-size");
    ADD_LIMIT_U32(maxVertexAttributes, "max-vertex-attributes");
    ADD_LIMIT_U32(maxVertexBufferArrayStride, "max-vertex-buffer-array-stride");
    ADD_LIMIT_U32(maxInterStageShaderVariables, "max-inter-stage-shader-variables");
    ADD_LIMIT_U32(maxColorAttachments, "max-color-attachments");
    ADD_LIMIT_U32(maxColorAttachmentBytesPerSample, "max-color-attachment-bytes-per-sample");
    ADD_LIMIT_U32(maxComputeWorkgroupStorageSize, "max-compute-workgroup-storage-size");
    ADD_LIMIT_U32(maxComputeInvocationsPerWorkgroup, "max-compute-invocations-per-workgroup");
    ADD_LIMIT_U32(maxComputeWorkgroupSizeX, "max-compute-workgroup-size-x");
    ADD_LIMIT_U32(maxComputeWorkgroupSizeY, "max-compute-workgroup-size-y");
    ADD_LIMIT_U32(maxComputeWorkgroupSizeZ, "max-compute-workgroup-size-z");
    ADD_LIMIT_U32(maxComputeWorkgroupsPerDimension, "max-compute-workgroups-per-dimension");

    return output;
}
