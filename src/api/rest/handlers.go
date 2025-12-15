package main

/*
#cgo LDFLAGS: -L../../../build/api -lzoro
#include "../c_api/zoro_c_api.h"
*/
import "C"

import (
    "net/http"
    "unsafe"

    "github.com/gin-gonic/gin"
)

func CreateCollection(c *gin.Context) {
    var req struct {
        Name      string `json:"name"`
        Dimension int    `json:"dimension"`
    }

    if err := c.ShouldBindJSON(&req); err != nil {
        c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
        return
    }

    errBuf := make([]byte, 256)

    ok := C.zoro_create_collection(
        C.CString(req.Name),
        C.int(req.Dimension),
        (*C.char)(unsafe.Pointer(&errBuf[0])),
    )

    if !ok {
        c.JSON(http.StatusBadRequest, gin.H{"error": string(errBuf)})
        return
    }

    c.Status(http.StatusCreated)
}

func DeleteCollection(c *gin.Context) {
    name := c.Param("name")
    errBuf := make([]byte, 256)

    ok := C.zoro_delete_collection(
        C.CString(name),
        (*C.char)(unsafe.Pointer(&errBuf[0])),
    )

    if !ok {
        c.JSON(http.StatusBadRequest, gin.H{
            "error": cString(errBuf),
        })
        return
    }

    c.Status(http.StatusNoContent)
}

func ListCollections(c *gin.Context) {
    c.JSON(http.StatusOK, gin.H{
        "collections": []string{},
    })
}


func cString(buf []byte) string {
    for i, b := range buf {
        if b == 0 {
            return string(buf[:i])
        }
    }
    return string(buf)
}
