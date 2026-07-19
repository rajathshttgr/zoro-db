# Benchmark

This benchmark evaluates the raw vector insertion and search performance
of **Zoro-DB**, a vector database built from scratch for
learning and experimentation.

The benchmark focuses on:

-   Vector insertion throughput
-   Search latency
-   Queries per second (QPS)

It intentionally **does not** evaluate ANN recall or search accuracy.

------------------------------------------------------------------------

## Test Configuration

  Parameter                       Value
  -------------------- ----------------
  Number of vectors             100,000
  Vector dimension                  384
  Distance metric                Cosine
  Payload / Metadata               None
  Batch size                      1,000
  Search queries                  1,000
  Top-K                              10
  Vector type            Random float32

------------------------------------------------------------------------

## Test Environment

### Hardware

  Component      Value
  -------------- ---------------------------------
  CPU            Intel Core i5-12450H (12th Gen)
  Logical CPUs   12
  RAM            16 GB
  Storage        512 GB NVMe SSD

The benchmark was executed on Ubuntu 24.04.2 LTS using Docker.

### Software

  Component          Version
  ------------------ --------------------
  Operating System   Ubuntu 24.04.2 LTS
  Kernel             Linux 6.17.0
  Python             3.12.3
  Docker             29.1.5

The database server was running inside a Docker container with default
runtime settings and no explicit CPU or memory limits.

------------------------------------------------------------------------

## Benchmark Results

### Upsert Performance

  Metric                                  Value
  ------------------ --------------------------
  Vectors Inserted                      100,000
  Total Time                          70.19 sec
  Throughput           **1,424.63 vectors/sec**

### Search Performance

  Metric                      Value
  ----------------- ---------------
  Queries                     1,000
  Top-K                          10
  Queries/sec              **5.31**
  Average Latency     **188.24 ms**
  Median Latency          180.82 ms
  P95 Latency             228.35 ms
  P99 Latency             303.74 ms
  Minimum Latency           5.75 ms
  Maximum Latency         400.01 ms

------------------------------------------------------------------------

## Benchmark Script

1.  Create a collection configured for cosine similarity.
2.  Generate 100,000 random 384-dimensional float32 vectors.
3.  Insert vectors in batches of 1,000 without payloads or metadata.
4.  Execute 1,000 search queries using randomly generated vectors.
5.  Record insertion throughput and search latency statistics.

------------------------------------------------------------------------

## Notes

-   Random vectors are generated using NumPy.
-   Payloads and metadata are disabled to measure raw vector storage and
    retrieval performance.
-   Search accuracy and recall are intentionally not evaluated.
-   All timings are measured from the Python client and include
    client-server communication overhead.
-   Results should be interpreted as a baseline for the current
    implementation rather than a comparison with mature production
    vector databases.
