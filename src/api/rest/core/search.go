package core

/*
#cgo LDFLAGS: -L../../../build/api -lzoro
#include "../c_api/zoro_c_api.h"
#include <stdlib.h>
*/
import "C"

import (
	"encoding/json"
	"errors"
	"unsafe"
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

	info := &PointRetrival{
		Status:  C.GoString(cPoint.status),
		PointId: int(cPoint.point_id),
		Payload: json.RawMessage(C.GoString(cPoint.payload)),
	}

	return info, nil
}
