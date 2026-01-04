FROM ubuntu:22.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive
ENV GO_VERSION=1.22.3

RUN apt-get update && apt-get install -y \
    build-essential \
    curl \
    git \
    ca-certificates \
    nlohmann-json3-dev \
    libopenblas-dev \
    liblapack-dev \
    && rm -rf /var/lib/apt/lists/*

# install CMake 
RUN curl -fsSL https://github.com/Kitware/CMake/releases/download/v3.27.9/cmake-3.27.9-linux-x86_64.tar.gz \
    | tar -xz --strip-components=1 -C /usr/local

RUN cmake --version

# Build FAISS 
RUN git clone --branch v1.7.4 --depth=1 \
    https://github.com/facebookresearch/faiss.git /tmp/faiss && \
    cd /tmp/faiss && \
    cmake -S . -B build \
        -DFAISS_ENABLE_GPU=OFF \
        -DFAISS_ENABLE_PYTHON=OFF \
        -DFAISS_ENABLE_C_API=ON \
        -DFAISS_ENABLE_OPENMP=OFF \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTING=OFF && \
    cmake --build build -j1 && \
    cmake --install build && \
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
    && rm -rf /var/lib/apt/lists/*

COPY --from=builder /app/src/build/zoro-db /app/zoro-db
COPY --from=builder /app/zoro-rest /app/zoro-rest
COPY --from=builder /app/src/build/api/libzoro.so /usr/local/lib/libzoro.so
COPY --from=builder /usr/local/lib/libfaiss.so /usr/local/lib/libfaiss.so

RUN ldconfig

RUN mkdir /storage
VOLUME ["/storage"]

EXPOSE 6464
CMD ["/app/zoro-rest"]
