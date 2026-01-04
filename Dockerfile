FROM ubuntu:22.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive
ENV GO_VERSION=1.22.3

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    curl \
    git \
    pkg-config \
    libopenblas-dev \
    libomp-dev \
    nlohmann-json3-dev \
    && rm -rf /var/lib/apt/lists/*

# Build FAISS (CPU-only)
RUN git clone --depth=1 https://github.com/facebookresearch/faiss.git /tmp/faiss && \
    cd /tmp/faiss && \
    cmake -B build -S . \
        -DFAISS_ENABLE_GPU=OFF \
        -DFAISS_ENABLE_PYTHON=OFF \
        -DFAISS_ENABLE_C_API=ON \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTING=OFF \
        -DFAISS_OPT_LEVEL=generic \
        -DBLAS_LIBRARIES=/usr/lib/x86_64-linux-gnu/libopenblas.so \
        -DBLAS_INCLUDE_DIRS=/usr/include && \
    cmake --build build -j$(nproc) && \
    cmake --install build && \
    ldconfig && \
    rm -rf /tmp/faiss

# Install Go
RUN curl -fsSL https://go.dev/dl/go${GO_VERSION}.linux-amd64.tar.gz \
    | tar -C /usr/local -xz

ENV PATH="/usr/local/go/bin:${PATH}"

WORKDIR /app
COPY src/ ./src/

# Build C++ core
WORKDIR /app/src
RUN mkdir -p build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make -j$(nproc)

# Build REST API
WORKDIR /app/src/api/rest
ENV LD_LIBRARY_PATH=/usr/local/lib:/app/src/build/api
RUN go build -o /app/zoro-rest

# Runtime image
FROM ubuntu:22.04

WORKDIR /app

ENV ZORO_DATA_PATH=/storage
ENV GIN_MODE=release
ENV LD_LIBRARY_PATH=/usr/local/lib

RUN apt-get update && apt-get install -y \
    libstdc++6 \
    libopenblas0 \
    libomp5 \
    && rm -rf /var/lib/apt/lists/*

# Copy binaries
COPY --from=builder /app/zoro-rest /app/zoro-rest
COPY --from=builder /app/src/build/zoro-db /app/zoro-db

# Copy shared libraries
COPY --from=builder /usr/local/lib/libfaiss.so /usr/local/lib/libfaiss.so
COPY --from=builder /app/src/build/api/libzoro.so /usr/local/lib/libzoro.so

RUN mkdir /storage
VOLUME ["/storage"]

EXPOSE 6464

CMD ["/app/zoro-rest"]
