package core

/*
#cgo LDFLAGS: -L../../../build/api -lzoro
#include "../c_api/zoro_c_api.h"
#include <stdlib.h>
*/
import "C"

// import (
// 	"errors"
// 	"unsafe"
// )

func UpsertPoints(collection_name string, vectors [][]float32, Ids []string, Payload []map[string]any,) error {

	// demo implementation
	return nil
}

