# Allowed Operations

1. CREATE_COLLECTION

   - collection_name/id, dimension, distance

2. DELETE_COLLECTION

   - collection_name/id

3. UPSERT_POINTS

   - collection_name/id, point_id, vectors, payload

4. DELETE_POINTS
   - collection_name/id, point_id

## Build (Module-Level)

```bash
mkdir build && cd build
cmake ..
make -j8
```
