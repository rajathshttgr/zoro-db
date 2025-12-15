FROM ubuntu:22.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive
ENV GO_VERSION=1.22.3

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    curl \
    git \
    nlohmann-json3-dev \
    && rm -rf /var/lib/apt/lists/*

# Install Go
RUN curl -fsSL https://go.dev/dl/go${GO_VERSION}.linux-amd64.tar.gz \
    | tar -C /usr/local -xz

ENV PATH="/usr/local/go/bin:${PATH}"

WORKDIR /app
COPY src/ ./src/

# Build C++ core
WORKDIR /app/src
RUN mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make -j$(nproc)

# Build REST API
WORKDIR /app/src/api/rest
ENV LD_LIBRARY_PATH=/app/src/build/api
RUN go build -o /app/zoro-rest

# Runtime image
FROM ubuntu:22.04

WORKDIR /app

RUN apt-get update && apt-get install -y \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

# Copy binaries
COPY --from=builder /app/src/build/zoro-db /app/zoro-db
COPY --from=builder /app/zoro-rest /app/zoro-rest

COPY --from=builder /app/src/build/api/libzoro.so /usr/local/lib/libzoro.so

RUN ldconfig

RUN mkdir /storage
VOLUME ["/storage"]

EXPOSE 6464
CMD ["/app/zoro-rest"]