# see https://github.com/WebAssembly/wasi-sdk?tab=readme-ov-file#use
# ex: export WASI_SDK_PATH=/Users/sean/Downloads/wasi-sdk-24.0-arm64-macos

clang := ${WASI_SDK_PATH}/bin/clang --sysroot=${WASI_SDK_PATH}/share/wasi-sysroot

build:
	$(clang) webgpu.c imports_component_type.o imports.c -o webgpu.wasm -mexec-model=reactor