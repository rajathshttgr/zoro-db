FROM ubuntu:22.04 AS builder

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    nlohmann-json3-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY src/ ./src/

WORKDIR /app/src
RUN mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make -j$(nproc)

FROM ubuntu:22.04

WORKDIR /app

COPY --from=builder /app/src/build/zoro-db /app/zoro-db

RUN mkdir /storage
VOLUME ["/storage"]

EXPOSE 9000

CMD ["/app/zoro-db"]
