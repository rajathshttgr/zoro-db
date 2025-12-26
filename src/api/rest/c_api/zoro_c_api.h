#pragma once
#include <stdbool.h>
#include "c_structs.h"

#ifdef __cplusplus
extern "C" {
#endif

bool zoro_init(const char* data_path, char* err);
void zoro_shutdown();

bool zoro_create_collection(const char* name, int dimension, const char* distance, char* err);
bool zoro_delete_collection(const char* name, char* err);

bool zoro_list_collections(
    zoro_collection_info_t** out_collections,
    int* out_count,
    char* err
);

void zoro_free_collections(
    zoro_collection_info_t* collections,
    int count
);

bool zoro_get_collection(
    const char* name,
    zoro_collection_info_t* out_info,
    char* err
);

void zoro_free_collection(zoro_collection_info_t* info);

#ifdef __cplusplus
}
#endif
