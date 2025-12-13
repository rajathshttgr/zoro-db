# ZORO-DB - Vector Search Engine

## Quick Start

### Prerequisites

- Linux or macOS (Windows users: WSL recommended)
- CMake ≥ 3.16
- g++ or clang++

### Build & Run

**1. Make the build script executable:**

```bash
chmod +x build.sh
```

**2. CLI Mode**

```bash
./build.sh
```

**3. REST API Mode**

```bash
./build.sh rest
```

Access the API at `http://localhost:8080`

## Roadmap

- [x] REST API
- [ ] WAL & Snapshots
- [ ] Hot Cache
