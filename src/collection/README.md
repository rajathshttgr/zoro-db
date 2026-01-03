# Collection Module

## Build (Module-Level)

```bash
mkdir build && cd build
cmake ..
make -j8
```

This builds the `collection` static library:

---

## Run Tests (Module-Level)

Enable tests when configuring:

```bash
mkdir build && cd build
cmake .. -DCOLLECTION_BUILD_TESTS=ON
make -j8
ctest
```

Or run the test binary directly:

```bash
./collection_tests
```

## TODO

- [ ] Input Validations
