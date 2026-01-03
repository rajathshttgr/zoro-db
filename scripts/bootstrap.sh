#!/bin/bash
set -e

echo "Installing system dependencies..."

# Update package index
sudo apt update

# Core build dependencies
sudo apt install -y \
    build-essential \
    cmake \
    git \
    nlohmann-json3-dev \
    libopenblas-dev

# Check if FAISS is already installed
if ! ldconfig -p | grep -q libfaiss; then
    echo "FAISS not found. Building FAISS (CPU-only)..."

    # Clean any previous failed attempts
    sudo rm -rf /tmp/faiss

    # Clone FAISS
    git clone https://github.com/facebookresearch/faiss.git /tmp/faiss
    cd /tmp/faiss

    # Configure FAISS (CPU-only, no tests, no Python)
    cmake -B build -S . \
        -DFAISS_ENABLE_GPU=OFF \
        -DFAISS_ENABLE_PYTHON=OFF \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTING=OFF

    # Build and install
    cmake --build build -j$(nproc)
    sudo cmake --install build

    # Cleanup
    cd /
    sudo rm -rf /tmp/faiss

    echo "FAISS installed successfully."
else
    echo "FAISS already installed. Skipping build."
fi

echo "Bootstrap complete."
