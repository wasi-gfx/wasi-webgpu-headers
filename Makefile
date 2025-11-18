# see https://github.com/WebAssembly/wasi-sdk?tab=readme-ov-file#use
# ex: export WASI_SDK_PATH=/Users/sean/Downloads/wasi-sdk-24.0-arm64-macos

clang := ${WASI_SDK_PATH}/bin/clang --sysroot=${WASI_SDK_PATH}/share/wasi-sysroot

tidy:
	${WASI_SDK_PATH}/bin/clang-tidy webgpu.c -- -I${WASI_SDK_PATH}/share/wasi-sysroot/include

analyze:
	${WASI_SDK_PATH}/bin/clang --analyze -Xanalyzer -analyzer-output=text -I${WASI_SDK_PATH}/share/wasi-sysroot/include webgpu.c

build-library:
	$(clang) webgpu.c imports_component_type.o imports.c -o webgpu.wasm -mexec-model=reactor

generate-bindings:
	# renaming poll so that it doesn't collide with other packages using poll
	wit-bindgen c wit --world imports --rename wasi:io/poll@0.2.0=webgpu_headers_poll
	wit-bindgen c wit --world wasi:cli/command@0.2.0 --out-dir examples

build-example:
	$(clang) examples/$(example)/main.c imports_component_type.o imports.c examples/command_component_type.o examples/command.c -o examples/$(example)/output.wasm -mexec-model=reactor
	wasm-tools component new ./examples/$(example)/output.wasm -o examples/$(example)/output.component.wasm
