package core

/*
#cgo LDFLAGS: -L../../../../build/api -lzoro
#include "../c_api/zoro_c_api.h"
#include <stdlib.h>
*/
import "C"

import (
	"os"
	"errors"
	"unsafe"
)

func Init(dataPath string) error {
	cPath := C.CString(dataPath)
	defer C.free(unsafe.Pointer(cPath))

	errBuf := C.malloc(256)
	defer C.free(errBuf)

	ok := C.zoro_init(cPath, (*C.char)(errBuf))
	if !ok {
		return errors.New(C.GoString((*C.char)(errBuf)))
	}

	return nil
}

func InitFromEnv() error {
    path := os.Getenv("ZORO_DATA_PATH")
    if path == "" {
        path = "/storage"
    }
    return Init(path)
}

func Shutdown() {
	C.zoro_shutdown()
}
