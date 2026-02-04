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


func SearchPointsByVector(
    collectionName string,
    vectors []float32,
    limit int,
) ([]*SearchPoint, error) {

    cName := C.CString(collectionName)
    defer C.free(unsafe.Pointer(cName))

    cVectors := (*C.float)(unsafe.Pointer(&vectors[0]))
    cLimit := C.int(limit)

    var cPoints *C.zoro_search_point_t
    var cCount C.int

    errBuf := C.malloc(256)
    defer C.free(errBuf)

    ok := C.zoro_search_points(
        cName,
        cVectors,
        C.size_t(len(vectors)),
        cLimit,
        &cPoints,
        &cCount,
        (*C.char)(errBuf),
    )

    if !ok {
        return nil, errors.New(C.GoString((*C.char)(errBuf)))
    }
    defer C.zoro_free_search_result(cPoints, cCount)

    count := int(cCount)
    results := make([]*SearchPoint, 0, count)

    slice := unsafe.Slice(cPoints, count)

    for _, cp := range slice {
        var payload map[string]any
        if err := json.Unmarshal(
            []byte(C.GoString(cp.payload)),
            &payload,
        ); err != nil {
            return nil, err
        }

        results = append(results, &SearchPoint{
            PointId: int(cp.point_id),
            Score:   float32(cp.score),
            Payload: payload,
        })
    }

    return results, nil
}

func ScrollPointsDataRetrival(
    collectionName string,
    limit int,
) ([]*ScrollPoint, error) {

    cName := C.CString(collectionName)
    defer C.free(unsafe.Pointer(cName))

    cLimit := C.int(limit)

    var cPoints *C.zoro_scroll_point_t
    var cCount C.int

    errBuf := C.malloc(256)
    defer C.free(errBuf)

    ok := C.zoro_scroll_points(
        cName,
        cLimit,
        &cPoints,
        &cCount,
        (*C.char)(errBuf),
    )

    if !ok {
        return nil, errors.New(C.GoString((*C.char)(errBuf)))
    }
    defer C.zoro_free_scroll_result(cPoints, cCount)

    count := int(cCount)
    results := make([]*ScrollPoint, 0, count)

    slice := unsafe.Slice(cPoints, count)

    for _, cp := range slice {
        var payload map[string]any
        if err := json.Unmarshal(
            []byte(C.GoString(cp.payload)),
            &payload,
        ); err != nil {
            return nil, err
        }

        results = append(results, &ScrollPoint{
            PointId: int(cp.point_id),
            Payload: payload,
        })
    }

    return results, nil
}