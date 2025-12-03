package engine

/*
#cgo CXXFLAGS: -std=c++17
#cgo LDFLAGS: -L../../engine/bin -lzoro_engine -lstdc++

#include <stdlib.h>
#include "../../engine/include/zoro_engine.hpp"
*/
import "C"
import (
	"errors"
	"unsafe"
)

// CreateCollection → Go wrapper for Zoro_CreateCollection
func CreateCollection(name string, dim int) error {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))

	result := C.Zoro_CreateCollection(cName, C.int(dim))
	if result != 0 {
		return errors.New("failed to create collection")
	}
	return nil
}

// InsertVector → Go wrapper for Zoro_InsertVector
func InsertVector(collection string, vector []float32) error {
	cName := C.CString(collection)
	defer C.free(unsafe.Pointer(cName))

	ptr := (*C.float)(unsafe.Pointer(&vector[0]))

	result := C.Zoro_InsertVector(cName, ptr, C.int(len(vector)))
	if result != 0 {
		return errors.New("failed to insert vector")
	}
	return nil
}
