#include "engine.hpp"
#include <cstring>

using namespace zoro;

static Engine* g_engine = nullptr;

extern "C" {

// Initialize engine;
int zoro_Init(const char* data_dir){
    if(g_engine) return 0;
    std::string dir = data_dir ? data_dir : "data";
    g_engine = new Engine(dir);
    return g_engine? 0: -1;
}  

// Create collection;
int zoro_CreateCollection(const char* name, int dimension){
    if (!g_engine) return -1;
    if(!name) return -1;

    return g_engine->create_collection(name, dimension)? 0: -1;
}

// Insert a vector (values is float array of length dim)
int zoro_InsertVector(const char* collection, const char* id, const float* values, int dim){
    if(!g_engine || !collection || !id || !values) return -1;
    auto col =g_engine->get_collection(collection);
    if(!col) return -1;
    Vector v;
    v.id = std::string(id);
    v.values.assign(values, values + dim);
    return col->insert(v)?0:-1;
}

// Get vector by id;
int zoro_GetVector(const char* collection, const char* id, float* out_values, int dim){
    if (!g_engine || !collection || !id || !out_values) return -1;
    auto col = g_engine->get_collection(collection);
    if (!col) return -1;
    Vector v;
    if (!col->get(id, v)) return -1;
    if ((int)v.values.size() != dim) return -1;
    std::memcpy(out_values, v.values.data(), sizeof(float) * dim);
    return 0;
}

// get collection size
int zoro_CollectionCount(const char* collection) {
    if (!g_engine || !collection) return -1;
    auto col = g_engine->get_collection(collection);
    if (!col) return -1;
    return (int)col->size();
}

// Shutdown
void zoro_Shutdown() {
    if (g_engine) {
    delete g_engine;
    g_engine = nullptr;
    }
}
}

