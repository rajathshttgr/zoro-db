package core

/*
#cgo LDFLAGS: -L../../../../build/api -lzoro
#include "../c_api/zoro_c_api.h"
#include <stdlib.h>
*/
import "C"

import (
	"unsafe"
	"errors"
	"encoding/json"
)

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

func UpsertPoints(
	collectionName string,
	vectors [][]float32,
	ids []int,
	payload []map[string]any,
) error {

	count := len(ids)
	if count == 0 {
		return nil
	}

	if len(vectors) != count || len(payload) != count {
		return errors.New("ids, vectors, and payload must have same length")
	}

	// Allocate C array for zoro_point_t
	cPoints := (*C.zoro_point_t)(
		C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(C.zoro_point_t{}))),
	)
	if cPoints == nil {
		return errors.New("failed to allocate C memory for points")
	}
	defer C.free(unsafe.Pointer(cPoints))

	// Track payload C strings for cleanup
	payloadPtrs := make([]*C.char, count)

	for i := 0; i < count; i++ {
		if len(vectors[i]) == 0 {
			return errors.New("vector length cannot be zero")
		}

		point := (*C.zoro_point_t)(
			unsafe.Add(
				unsafe.Pointer(cPoints),
				i*int(unsafe.Sizeof(C.zoro_point_t{})),
			),
		)

		// ID
		point.id = C.int(ids[i])

		// Vector (read-only, Go memory is OK during call)
		point.vector = (*C.float)(unsafe.Pointer(&vectors[i][0]))
		point.vector_len = C.size_t(len(vectors[i]))

		// Payload → JSON string
		payloadJSON, err := json.Marshal(payload[i])
		if err != nil {
			return err
		}

		cPayload := C.CString(string(payloadJSON))
		payloadPtrs[i] = cPayload
		point.payload = cPayload
	}

	// Free payload strings
	defer func() {
		for _, p := range payloadPtrs {
			if p != nil {
				C.free(unsafe.Pointer(p))
			}
		}
	}()

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

	ok := C.zoro_upsert_points(
		cCollection,
		cPoints,
		C.size_t(count),       
		cErr,
		C.size_t(errBufSize),
	)

	if !ok {
		return errors.New(C.GoString(cErr))
	}

	return nil
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


func GetPointById(collectionName string, pointId int) (*PointRetrival, error) {
	cName := C.CString(collectionName)
	defer C.free(unsafe.Pointer(cName))

	cId := C.int(pointId)

	var cPoint C.zoro_point_retrival_t

	errBuf := C.malloc(256)
	defer C.free(errBuf)

	ok := C.zoro_point_retrival(
		cName,
		&cId,
		&cPoint,
		(*C.char)(errBuf),
	)

	if !ok {
		return nil, errors.New(C.GoString((*C.char)(errBuf)))
	}

	// free C-allocated strings after copying
	defer C.zoro_free_point_retrival(&cPoint)

	var payload map[string]any
	if err := json.Unmarshal(
		[]byte(C.GoString(cPoint.payload)),
		&payload,
	); err != nil {
		return nil, err
	}

	info := &PointRetrival{
		Status:  C.GoString(cPoint.status),
		PointId: int(cPoint.point_id),
		Payload: payload,
	}

	return info, nil
}