#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const char* name;
    int size;
    const char* distance;
    const char* status;
} collection_metadata_t;

typedef struct {
    const char* name;
    int size;
    const char* distance;
    const char* status;

    int points_count;
    int segments_count;
    const char* collection_id;
    const char* created_at;
    const char* updated_at;

    const char* index;
    bool gpu_support;
    bool parallel_boost;

    int id;
    int dimension;
    const char* coll_name;
    
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
    const char* payload;
} zoro_point_scroll_t;

typedef struct {
    int point_id;
    float score;
    const char* payload;
} zoro_search_point_t;

typedef struct {
    int point_id;
    const char* payload;
} zoro_scroll_point_t;


#ifdef __cplusplus
}
#endif
