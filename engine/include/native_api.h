#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Initialize engine
int zoro_Init();

// Create collection
// int zoro_CreateCollection(const char* name, int dimension);

// Shutdown engine
void zoro_Shutdown();

#ifdef __cplusplus
}
#endif
