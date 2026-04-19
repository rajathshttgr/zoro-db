package core

/*
#cgo LDFLAGS: -L../../../../build/bridge -lzoro
#include "../../bridge/zoro_c_api.h"
#include <stdlib.h>
*/
import "C"

import (
	"unsafe"
	"errors"
	"encoding/json"
	"zoro/dto"
)

func UpsertPoints(
	collectionName string,
	points []dto.PointData,
) (int, error) {

	count := len(points)
	if count == 0 {
		return -1, errors.New("points must not be empty")
	}

	pointSize := unsafe.Sizeof(C.zoro_point_t{})

	// Allocate contiguous C memory
	cPoints := C.malloc(C.size_t(count) * C.size_t(pointSize))
	if cPoints == nil {
		return -1, errors.New("failed to allocate C memory for points")
	}
	defer C.free(cPoints)

	// Keep payload pointers for cleanup (minimal overhead)
	payloadPtrs := make([]unsafe.Pointer, 0, count)

	for i := 0; i < count; i++ {
		point := (*C.zoro_point_t)(
			unsafe.Add(cPoints, uintptr(i)*pointSize),
		)

		p := &points[i]

		// ID
		point.id = C.int(p.Id)

		// Vector - no copy, just pointer
		if len(p.Vector) > 0 {
			point.vector = (*C.float)(unsafe.Pointer(&p.Vector[0]))
			point.vector_len = C.size_t(len(p.Vector))
		}

		// Payload - JSON
		payloadJSON, err := json.Marshal(p.Payload)
		if err != nil {
			return -1, err
		}

		cPayload := C.CString(string(payloadJSON))
		
		payloadPtrs = append(payloadPtrs, unsafe.Pointer(cPayload))
		point.payload = cPayload
	}

	// Cleanup payloads
	defer func() {
		for _, p := range payloadPtrs {
			C.free(p)
		}
	}()

	// Error buffer (stack-like usage)
	const errBufSize = 512
	cErr := C.malloc(errBufSize)
	if cErr == nil {
		return -1, errors.New("failed to allocate error buffer")
	}
	defer C.free(cErr)

	// Collection name
	cCollection := C.CString(collectionName)
	defer C.free(unsafe.Pointer(cCollection))

	operationId := C.int(-1)

	ok := C.zoro_upsert_points(
		cCollection,
		(*C.zoro_point_t)(cPoints),
		C.size_t(count),
		(*C.int)(unsafe.Pointer(&operationId)), 
		(*C.char)(cErr),
		C.size_t(errBufSize),
	)

	if !ok {
		return -1, errors.New(C.GoString((*C.char)(cErr)))
	}

	return int(operationId), nil
}


func DeletePoints(
	collectionName string,
	ids []int,
) error {

	count := len(ids)
	if count == 0 {
		return nil
	}

	// Allocate C array for point IDs
	cIDs := (*C.int)(
		C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(C.int(0)))),
	)
	if cIDs == nil {
		return errors.New("failed to allocate C memory for point IDs")
	}
	defer C.free(unsafe.Pointer(cIDs))

	for i := 0; i < count; i++ {
		*(*C.int)(unsafe.Add(unsafe.Pointer(cIDs), i*int(unsafe.Sizeof(C.int(0))))) = C.int(ids[i])
	}

	// Error buffer
	const errBufSize = 512
	cErr := (*C.char)(C.malloc(errBufSize))
	if cErr == nil {
		return errors.New("failed to allocate error buffer")
	}
	defer C.free(unsafe.Pointer(cErr))

	// Collection name
	cCollection := C.CString(collectionName)
	defer C.free(unsafe.Pointer(cCollection))

	ok := C.zoro_delete_points(
		cCollection,
		cIDs,
		C.size_t(count),       
		cErr,
		C.size_t(errBufSize),
	)

	if !ok {
		return errors.New(C.GoString(cErr))
	}

	return nil
}

func CountPoints(collection_name string) (int, error) {
	// convert Go string to C string
	cCollectionName := C.CString(collection_name)
	defer C.free(unsafe.Pointer(cCollectionName))

	// Allocate C error buffer
	errBuf := C.malloc(256)
	defer C.free(errBuf)

	count := C.zoro_count_points(
		cCollectionName,
		(*C.char)(errBuf),
	)

	if count == -1 {
		return 0, errors.New(C.GoString((*C.char)(errBuf)))
	}

	return int(count), nil
}