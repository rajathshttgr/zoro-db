package core

/*
#cgo LDFLAGS: -L../../../build/api -lzoro
#include "../c_api/zoro_c_api.h"
#include <stdlib.h>
*/
import "C"

import (
	"errors"
	"unsafe"
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

func ListCollections() ([]CollectionInfo, error) {
	var cCollections *C.zoro_collection_info_t
	var cCount C.int

	// Allocate error buffer
	errBuf := C.malloc(256)
	defer C.free(errBuf)

	ok := C.zoro_list_collections(
		(**C.zoro_collection_info_t)(&cCollections),
		(*C.int)(&cCount),
		(*C.char)(errBuf),
	)

	if !ok {
		return nil, errors.New(C.GoString((*C.char)(errBuf)))
	}

	count := int(cCount)
	defer C.zoro_free_collections(cCollections, cCount)

	// Convert C array → Go slice
	cSlice := unsafe.Slice(cCollections, count)

	collections := make([]CollectionInfo, 0, count)

	for _, c := range cSlice {
		collections = append(collections, CollectionInfo{
			ID:        int(c.id),
			Name:      C.GoString(c.name),
			Dimension: int(c.dimension),
			Distance:  C.GoString(c.distance),
			Status:    C.GoString(c.status),
			CreatedAt: C.GoString(c.created_at),
		})
	}

	return collections, nil
}


func GetCollectionInfo(collectionName string) (*CollectionInfo, error) {
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
    info := &CollectionInfo{
        ID:        int(cInfo.id),
        Name:      C.GoString(cInfo.name),
        Dimension: int(cInfo.dimension),
        Distance:  C.GoString(cInfo.distance),
        Status:    C.GoString(cInfo.status),
        CreatedAt: C.GoString(cInfo.created_at),
    }

    return info, nil
}

