# Contributing to Zoro-DB

Thanks for your interest in contributing to Zoro-DB.
This guide explains how to build, run, and make small contributions to the project.

### Prerequisites

- Linux or macOS (Windows users: WSL recommended)
- CMake ≥ 3.16
- g++ or clang++
- Go ≥ 1.22 (only for REST API)

> System deps like **nlohmann-json** and **FAISS (CPU-only)** can be installed automatically using the bootstrap script.

## Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/rajathshttgr/zoro-db.git
cd zoro-db
```

### 2. Install system dependencies (recommended)

```bash
chmod +x scripts/bootstrap.sh
./scripts/bootstrap.sh
```

### 3. Build & run (REST API – default)

```bash
chmod +x scripts/build.sh
./scripts/build.sh
```

The REST API will be available at:

```
http://localhost:6464
```

### 4. Build & run (CLI – optional)

```bash
./scripts/build.sh cli
```

## Contribution Notes

- Create feature or fix branches from main
- Keep changes focused and easy to review
- Follow existing code style and structure

### Commit messages

Use a simple prefix:

- `feat`: new feature
- `fix`: bug fix
- `docs`: documentation changes
- `tests`: tests only
- `chore`: refactor, cleanup, tooling

Example:

```
feat: add basic index search
fix: prevent crash on empty input
```

## Notes

- Build artifacts are generated in the `build/` directory.
- Persistent data is stored in `.zoro-data/` at the project root.
- FAISS is optional unless you are working on indexing/search features.
