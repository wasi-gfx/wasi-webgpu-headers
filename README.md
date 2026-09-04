# wasi-webgpu-headers
wasi-webgpu implementation of [webgpu native headers](https://github.com/webgpu-native/webgpu-headers).

## Install wit dependencies
```shell
wkg wit fetch
```

## Generate wit bindings
```shell
make generate-bindings
```

## Build an example
```shell
make build-example example=[example]
```

### Available examples
- hello-triangle
- hello-compute
