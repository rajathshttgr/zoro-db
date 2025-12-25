# WAL (Write Ahead Logs)

## Build (Module-Level)

```bash
mkdir build && cd build
cmake ..
make -j8
```

This builds the `wal` static library:

---

## Run Tests (Module-Level)

Enable tests when configuring:

```bash
mkdir build && cd build
cmake .. -DWAL_BUILD_TESTS=ON
make -j8
ctest
```

Or run the test binary directly:

```bash
./wal_tests
```

## Project Status
