#pragma once
#include <stddef.h>

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

typedef struct {
    int id;
    const float* vector;
    size_t vector_len;
    const char* payload;  
} zoro_point_t;

typedef struct {
    const char* status;
    int point_id;
    const char* payload;
} zoro_point_retrival_t;

typedef struct {
    int point_id;
    int score;
    const char* payload;
} zoro_search_point_t;


#ifdef __cplusplus
}
#endif
