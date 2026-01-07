# REST API

## Overview

This REST API layer provides HTTP endpoints for the Zoro-DB service. It leverages CGO to interact with C++ components through C bindings, enabling high-performance database operations while maintaining a Go-based HTTP server.

## Architecture

### CGO & C++ Interaction

- **Go REST Handler** → **C Wrapper** → **C++ Implementation**
- CGO allows direct calls to C functions from Go code
- C acts as a bridge between Go and C++ type systems
- C++ database logic is compiled and linked at build time

### API Layer

The REST API exposes database operations (query, insert, update, delete) as HTTP endpoints, with request/response handling in Go while leveraging optimized C++ routines for core database operations.

## Run REST API in Dev Mode

```bash
go run .
```

## Run REST API in Release Mode

```bash
GIN_MODE=release go run .
```
