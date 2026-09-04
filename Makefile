# see https://github.com/WebAssembly/wasi-sdk?tab=readme-ov-file#use
# ex: export WASI_SDK_PATH=/Users/sean/Downloads/wasi-sdk-24.0-arm64-macos

clang := ${WASI_SDK_PATH}/bin/clang --sysroot=${WASI_SDK_PATH}/share/wasi-sysroot

tidy:
	${WASI_SDK_PATH}/bin/clang-tidy webgpu.c -- -I${WASI_SDK_PATH}/share/wasi-sysroot/include

analyze:
	${WASI_SDK_PATH}/bin/clang --analyze -Xanalyzer -analyzer-output=text -I${WASI_SDK_PATH}/share/wasi-sysroot/include webgpu.c

build-library:
	$(clang) webgpu.c async_futures.c imports_component_type.o imports.c -o webgpu.wasm -mexec-model=reactor

generate-bindings:
	wit-bindgen c wit --world imports
	# webgpu's async imports stay async (subtask ABI), but `run` is lifted sync so
	# examples can block in wgpuInstanceWaitAny to drive them to completion.
	wit-bindgen c wit --world wasi:cli/command@0.3.0 --out-dir examples --async=-export:wasi:cli/run@0.3.0#run

build-example:
	$(clang) examples/$(example)/main.c async_futures.c imports_component_type.o imports.c examples/command_component_type.o examples/command.c -o examples/$(example)/output.wasm -mexec-model=reactor
	wasm-tools component new ./examples/$(example)/output.wasm -o examples/$(example)/output.component.wasm
