# Storage Module

## Build (Module-Level)

```bash
mkdir build && cd build
cmake ..
make -j8
```

This builds the `storage` static library:

---

## Run Tests (Module-Level)

Enable tests when configuring:

```bash
mkdir build && cd build
cmake .. -DSTORAGE_BUILD_TESTS=ON
make -j8
ctest
```

Or run the test binary directly:

```bash
./storage_tests
```

## TODO

- [x] Catalog management
- [x] Collection metadata
- [x] File utilities
- [x] Core StorageEngine
- [ ] Shards Management
- [x] Upsert Points
