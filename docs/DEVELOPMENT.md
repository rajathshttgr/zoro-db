# Development Guide

This guide explains how to run and develop **Zoro-DB locally**.

# Prerequisites

- Linux or macOS
- CMake ≥ 3.16
- g++ or clang++
- Go ≥ 1.22 (for REST API)

> Windows users can use **WSL**.

System dependencies such as **nlohmann-json** and **FAISS (CPU)** can be installed automatically using the bootstrap script.

# Clone the Repository

```bash
git clone https://github.com/rajathshttgr/zoro-db.git
cd zoro-db
```

# Install Dependencies

Run the bootstrap script:

```bash
chmod +x scripts/bootstrap.sh
./scripts/bootstrap.sh
```

This installs required system libraries.

# Build and Run

Build the project and start the REST API:

```bash
chmod +x scripts/build.sh
./scripts/build.sh
```

The API will be available at:

```
http://localhost:6464
```

Build artifacts are created in:

```
build/
```

Persistent database files are stored in:

```
.zoro-data/
```

# Running with Docker

## Build the Docker Image

From the project root:

```bash
docker build -t zoro-db .
```

## Run the REST API

```bash
docker run -p 6464:6464 zoro-db
```

The API will be available at:

```
http://localhost:6464
```

## Testing Changes

After modifying the code:

1. Rebuild the project

```bash
./scripts/build.sh
```

2. Start the server

3. Test API endpoints locally.

# Notes

- FAISS is optional unless working on indexing or search features.
- Use Docker if you prefer a clean development environment.

# Need Help?

If you run into any issues while setting up the development environment, please open an issue and we'll get back to you soon.
