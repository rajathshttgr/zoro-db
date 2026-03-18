FROM ubuntu:24.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive
ENV GO_VERSION=1.22.3

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    curl \
    ca-certificates \
    nlohmann-json3-dev \
    libopenblas-dev \
    liblapack-dev \
    && rm -rf /var/lib/apt/lists/*

# Install Go
RUN curl -fsSL https://go.dev/dl/go${GO_VERSION}.linux-amd64.tar.gz \
    | tar -C /usr/local -xz

ENV PATH="/usr/local/go/bin:$PATH"

# Build FAISS
WORKDIR /build

RUN git clone --depth=1 --branch v1.7.4 https://github.com/facebookresearch/faiss.git

RUN cmake -S faiss -B faiss/build \
    -DFAISS_ENABLE_GPU=OFF \
    -DFAISS_ENABLE_PYTHON=OFF \
    -DFAISS_ENABLE_C_API=ON \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_TESTING=OFF

RUN cmake --build faiss/build --parallel $(nproc)
RUN cmake --install faiss/build

# Build Application
WORKDIR /app

COPY src ./src

# Build C++ core
RUN cmake -S src -B build -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build --parallel $(nproc)

# Build Go REST API
ENV CGO_CFLAGS="-I/app/src/bridge"
ENV CGO_LDFLAGS="-L/app/build/bridge"
ENV LD_LIBRARY_PATH=/app/build/bridge

WORKDIR /app/src/api

RUN go build -o /app/zoro-rest

# Runtime 
FROM ubuntu:24.04

WORKDIR /app

ENV ZORO_DATA_PATH=/storage
ENV GIN_MODE=release
ENV LD_LIBRARY_PATH=/usr/local/lib

# Install runtime libraries
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    libopenblas0 \
    libgomp1 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Copy binaries and libraries
COPY --from=builder /app/zoro-rest /app/zoro-rest
COPY --from=builder /app/build/bridge/libzoro.so /usr/local/lib/
COPY --from=builder /usr/local/lib/libfaiss* /usr/local/lib/

RUN ldconfig

# Storage for database
RUN mkdir /storage
VOLUME ["/storage"]

EXPOSE 6464

CMD ["/app/zoro-rest"]