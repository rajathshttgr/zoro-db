package native

/*
// Dedicated file for CGO directives and the native function wrapper.
#cgo CXXFLAGS: -std=c++17 -I${SRCDIR}/../../engine/include
#cgo LDFLAGS: -L${SRCDIR}/../../engine/build -lzoro -lstdc++

#include "native_api.h"
#include <stdlib.h>
*/
import "C"

import "errors"

// InitEngine is the wrapper for the C function zoro_Init() defined in the header.
func InitEngine() error {
    if C.zoro_Init() != 0 {
        return errors.New("failed to initialize native C++ engine")
    }
    return nil
}