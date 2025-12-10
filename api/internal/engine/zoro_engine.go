package engine

import (
    // Import the new package relative to your module root (zoro-api)
    "zoro-api/internal/native" 
)

// The CGO block is GONE from this file.

func InitEngine() error {
    // Call the function now implemented in the native package.
    return native.InitEngine()
}