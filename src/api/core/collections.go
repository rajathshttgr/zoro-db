package core

/*
#cgo LDFLAGS: -L../../../../build/bridge -lzoro
#include "../../bridge/zoro_c_api.h"
#include <stdlib.h>
*/
import "C"

import (
	"errors"
	"unsafe"
	"fmt"
	"zoro/dto"
)

func CreateCollection(name string, dimension int, distance string) error {
	// Convert Go string → C string
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))
	cDistance := C.CString(distance)

	// Allocate C error buffer
	errBuf := C.malloc(256)
	defer C.free(errBuf)

	ok := C.zoro_create_collection(
		cName,
		C.int(dimension),
		cDistance,
		(*C.char)(errBuf),
	)

	if !ok {
		return errors.New(C.GoString((*C.char)(errBuf)))
	}

	return nil
}


func DeleteCollection(collection_name string) error{
	// convert Go string to C string
	cCollectionName:= C.CString(collection_name)

	// Allocate C error buffer
	errBuf := C.malloc(256)
	defer C.free(errBuf)

	ok := C.zoro_delete_collection(
		cCollectionName,
		(*C.char)(errBuf),
	)

	if !ok {
		return errors.New(C.GoString((*C.char)(errBuf)))
	}

	return nil
}

func ListCollections() ([]dto.CollectionInfo, error) {
	var cCollections *C.collection_metadata_t
	var cCount C.int

	errBuf := C.malloc(256)
	defer C.free(errBuf)

	ok := C.zoro_list_collections(
		(**C.collection_metadata_t)(&cCollections),
		(*C.int)(&cCount),
		(*C.char)(errBuf),
	)

	if !ok {
		return nil, errors.New(C.GoString((*C.char)(errBuf)))
	}

	count := int(cCount)
	defer C.zoro_free_collections(cCollections, cCount)

	cSlice := unsafe.Slice(cCollections, count)

	collections := make([]dto.CollectionInfo, 0, count)

	for _, c := range cSlice {
		collections = append(collections, dto.CollectionInfo{
			Name:     C.GoString(c.name),
			Size:     int(c.size),
			Distance: C.GoString(c.distance),
			Status:   C.GoString(c.status),
		})
	}

	return collections, nil
}

func GetCollectionInfo(collectionName string) (*dto.CollectionInfo, error) {
    cName := C.CString(collectionName)
    defer C.free(unsafe.Pointer(cName))

    var cInfo C.zoro_collection_info_t

    errBuf := C.malloc(256)
    defer C.free(errBuf)

    ok := C.zoro_get_collection(
        cName,
        &cInfo,
        (*C.char)(errBuf),
    )

    if !ok {
        return nil, errors.New(C.GoString((*C.char)(errBuf)))
    }

    // free C-allocated strings after copying
    defer C.zoro_free_collection(&cInfo)

    // Convert to Go struct
    info := &dto.CollectionInfo{
        Name:      C.GoString(cInfo.name),
        Size:      int(cInfo.dimension),
        Distance:  C.GoString(cInfo.distance),
        Status:    C.GoString(cInfo.status),
    }

    return info, nil
}

func CheckCollectionExists(name string) (bool, error) {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))

	errBuf := C.malloc(256)
	defer C.free(errBuf)

	exists := C.zoro_check_collection_exists(
		cName,
		(*C.char)(errBuf),
	)

	errStr := C.GoString((*C.char)(errBuf))

	if errStr != "" {
		return false, fmt.Errorf(errStr)
	}

	return bool(exists), nil
}