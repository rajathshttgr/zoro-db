#!/bin/bash
set -e

MODE=${1:-cli}   
BUILD_DIR="build"

ROOT_DIR=$(cd "$(dirname "$0")/.." && pwd)

export ZORO_DATA_PATH="$ROOT_DIR/.zoro-data"
mkdir -p "$ZORO_DATA_PATH"

echo "Build mode: $MODE"

# Build C++ core
mkdir -p $BUILD_DIR
cd $BUILD_DIR

cmake ..
make -j$(nproc)

cd ..

if [ "$MODE" == "cli" ]; then
    echo "Running Zoro CLI..."
    ./build/zoro-db

elif [ "$MODE" == "rest" ]; then
    echo "Running Zoro REST API..."

    export LD_LIBRARY_PATH=$(pwd)/build/api:$LD_LIBRARY_PATH

    cd api/rest
    go run .

else
    echo "Unknown mode: $MODE"
    echo "Usage: ./build.sh [cli|rest]"
    exit 1
fi
