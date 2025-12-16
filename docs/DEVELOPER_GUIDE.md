# Zoro-DB Developer Guide

## Table of Contents

1. Overview
2. Running Zoro-DB with Docker
   - Detached Mode
   - Persistent Storage
   - Custom Port
3. Managing Containers
   - Stopping the Container
   - Checking Container Status
   - Removing Containers and Volumes
4. Port Conflicts
5. Using the CLI
6. Notes

---

## Overview

This guide covers all the essential commands and best practices for developers using **Zoro-DB** with Docker. It includes persistent storage, detached mode, container management, and troubleshooting common issues.

---

## Running Zoro-DB with Docker

### Detached Mode

Run Zoro-DB in the background (detached mode):

```
docker run -d -p 6464:6464 --name zoro-db ghcr.io/rajathshttgr/zoro-db:dev
```

- `-d` → Detached mode
- `--name zoro-db` → Assigns a name to the container

You can check the logs anytime:

```
docker logs -f zoro-db
```

---

### Persistent Storage

To keep data even if the container stops or is removed, mount a local folder as a Docker volume:

```
docker run -d -p 6464:6464 \
  -v $(pwd)/zoro-data:/app/data \
  --name zoro-db ghcr.io/rajathshttgr/zoro-db:dev
```

- `-v $(pwd)/zoro-data:/app/data` → Maps your local folder to the container's data directory.
- All vector collections will persist in `./zoro-data`.

---

### Custom Port

If port `6464` is in use, map to another port:

```
docker run -d -p 6565:6464 --name zoro-db ghcr.io/rajathshttgr/zoro-db:dev
```

- Container still uses `6464` internally.
- Access externally via `http://localhost:6565`.

---

## Managing Containers

### Stopping the Container

```
docker stop zoro-db
```

To remove it completely:

```
docker rm zoro-db
```

---

### Checking Container Status

List running containers:

```
docker ps
```

List all containers (running or stopped):

```
docker ps -a
```

---

### Removing Containers and Volumes

Remove a container and its associated volumes:

```
docker rm -v zoro-db
```

Remove all unused volumes:

```
docker volume prune
```

> **Caution:** This deletes data stored in volumes not currently used by containers.

---

## Port Conflicts

If the port is already in use:

1. Find which process uses the port:

```
lsof -i :6464
```

2. Kill the process (Linux/macOS):

```
kill -9 <PID>
```

3. Restart Zoro-DB with the same or a new port.

---

## Using the CLI

For debugging or development:

```
docker run -it --rm ghcr.io/rajathshttgr/zoro-db:dev /app/zoro-db

```

- `--rm` → Automatically remove container after exit.

---

## Notes

- Use persistent storage in production or long-term testing.
- Detached mode is recommended for background services.
- Always check port availability before running containers.
- CLI usage is optional and mostly for debugging.
