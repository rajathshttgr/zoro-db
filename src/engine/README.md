## Build & Run

- `mkdir build`
- `cd build`
- `cmake ..`
- `make -j8`

- `cd bin`
- `./engine_cli`

## Notes

- `/var/lib/zoro-db` (deafult data location for prod)

## Version dictionary

- `v0.0.1` Project Initialization, Collections CRUD Operations

## To do:

- [x] set collection <collection_name>
- [ ] get collection <collection_id>
- [ ] del collection <collection_id>

- [ ] set point {payload, vector}
- [ ] get point <point_id>
- [ ] del point <point_id>

- [ ] Read Database Version

- [ ] Run vector similarity search [collection_id, input_vector] returns point id which match input vector.
