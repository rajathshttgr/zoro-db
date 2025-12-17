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

func CreateCollection(name string, dimension int) error {
	// Convert Go string → C string
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))

	// Allocate C error buffer
	errBuf := C.malloc(256)
	defer C.free(errBuf)

	ok := C.zoro_create_collection(
		cName,
		C.int(dimension),
		(*C.char)(errBuf),
	)

	if !ok {
		return errors.New(C.GoString((*C.char)(errBuf)))
	}

	return nil
}
