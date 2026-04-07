# Services Module

## Responsbilities

- Strict business logic validations
- Standard data format conversion
- Metadata Cache lookup and rebuild
- Timout and health monitor

## Build (Module-Level)

```bash
mkdir build && cd build
cmake ..
make -j8
```

This builds the `service` static library:

## Run Unit Tests (Module-Level)

```bash
mkdir build && cd build
# Enable tests
cmake .. -DBUILD_TESTS=ON
make -j8
```

```bash
ctest
# or
./unit_tests
```

> Note: Detailed unit tests and integration tests scripts and documentations are available in `tests` above instructions are only for quick testing and not recommended.
