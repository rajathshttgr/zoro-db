#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool zoro_init(const char* data_path, char* err);
void zoro_shutdown();

bool zoro_create_collection(const char* name, int dimension, const char* distance, char* err);
bool zoro_delete_collection(const char* name, char* err);

#ifdef __cplusplus
}
#endif
