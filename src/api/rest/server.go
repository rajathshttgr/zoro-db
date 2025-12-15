package main

/*
#cgo LDFLAGS: -L../../build/api -lzoro
#include "../c_api/zoro_c_api.h"
*/
import "C"

import (
    "log"
    "unsafe"

    "github.com/gin-gonic/gin"
)

func main() {
    errBuf := make([]byte, 256)

    ok := C.zoro_init(
        C.CString("/tmp/zoro-data"),
        (*C.char)(unsafe.Pointer(&errBuf[0])),
    )

    if !ok {
        log.Fatalf("zoro_init failed: %s", cString(errBuf))
    }

    r := gin.Default()

    r.GET("/", func(c *gin.Context) {
        c.JSON(200, gin.H{
            "message": "Welcome to Zoro DB API",
        })
    })
    
    r.POST("/collections", CreateCollection)
    r.DELETE("/collections/:name", DeleteCollection)
    r.GET("/collections", ListCollections)

    log.Println("Listening on :6464")
    r.Run(":6464")
}
