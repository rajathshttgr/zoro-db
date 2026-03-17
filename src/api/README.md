# Zoro-DB REST API

## Overview

- Go-based HTTP server
- CGO to interact with C++ component through C bindings
- C++ Core System logics are compiled and directly linked at build time

## Run REST API in Dev Mode

From the project root run:

```bash
go run .
```

## Run REST API in Release Mode

```bash
GIN_MODE=release go run .
```

> Note: api components are depends on core database system (c++), so you need to run both service together.
