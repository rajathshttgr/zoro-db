#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int id;
    const char* name;
    int dimension;
    const char* distance;
    const char* status;
    const char* created_at;
} zoro_collection_info_t;

#ifdef __cplusplus
}
#endif
