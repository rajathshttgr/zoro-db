# Collection Module

## Build (Module-Level)

```bash
mkdir build && cd build
cmake ..
make -j8
```

This builds the `core` static library:

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
./core_tests
```

## TODO

- [ ] Input Validations
