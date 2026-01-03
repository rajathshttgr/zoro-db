#!/bin/bash
set -e

MODE=${1:-rest}
BUILD_DIR="build"

# Root of repo (zoro-db/)
ROOT_DIR=$(cd "$(dirname "$0")/.." && pwd)

SRC_DIR="$ROOT_DIR/src"
BUILD_PATH="$ROOT_DIR/$BUILD_DIR"

export ZORO_DATA_PATH="$ROOT_DIR/.zoro-data"
mkdir -p "$ZORO_DATA_PATH"

echo "Build mode: $MODE"
echo "Project root: $ROOT_DIR"

# Build C++ core
mkdir -p "$BUILD_PATH"
cd "$BUILD_PATH"

cmake "$SRC_DIR"
make -j$(nproc)

if [ "$MODE" == "cli" ]; then
    echo "Running Zoro CLI..."
    ./zoro-db

elif [ "$MODE" == "rest" ]; then
    echo "Running Zoro REST API..."

    export LD_LIBRARY_PATH="$BUILD_PATH/api:$LD_LIBRARY_PATH"

    cd "$SRC_DIR/api/rest"
    go run .

else
    echo "Unknown mode: $MODE"
    echo "Usage: ./scripts/build.sh [cli|rest]"
    exit 1
fi
