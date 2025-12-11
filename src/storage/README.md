# Storage Module

The **Storage** component of _zoro-db_ implements low-level storage operations including:

- Catalog management
- Collection metadata
- File utilities
- Core StorageEngine

---

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

- [ ] Add Tests for all files
