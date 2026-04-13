# Collection Module

## Responsbilities

- Manages all collection level operations
- Coordinates WAL, disk storage and indexing
- Builds Fast Retrival Cache for Frequently accessed or Recently accessed data
- Action planer and it don't handle io data validations.
- Index build and Maintainence
- StartUp and WAL checking and crash recovery

## Build (Module-Level)

```bash
mkdir build && cd build
cmake ..
make -j8
```

This builds the `collection` static library:

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
