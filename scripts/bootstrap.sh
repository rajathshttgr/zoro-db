#!/bin/bash
set -e

echo "Installing system dependencies..."

sudo apt update
sudo apt install -y \
    build-essential \
    cmake \
    git \
    nlohmann-json3-dev \
    libopenblas-dev

if ! ldconfig -p | grep -q libfaiss; then
    echo "FAISS not found. Building FAISS (CPU-only)..."
    git clone https://github.com/facebookresearch/faiss.git /tmp/faiss
    cd /tmp/faiss

    cmake -B build -S . \
      -DFAISS_ENABLE_GPU=OFF \
      -DFAISS_ENABLE_PYTHON=OFF \
      -DBUILD_SHARED_LIBS=ON

    cmake --build build -j$(nproc)
    sudo cmake --install build
    rm -rf /tmp/faiss
else
    echo "FAISS already installed."
fi

echo "Bootstrap complete."
