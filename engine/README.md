# ZORO C++ Engine

This folder contains a minimal C++ engine scaffold for ZORO. It builds a shared library `libzoro.so` exposing a tiny C API for integration with other languages (Go via cgo).

## Build

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

The build will produce `libzoro.so` in the build directory (or library path depending on your platform).
