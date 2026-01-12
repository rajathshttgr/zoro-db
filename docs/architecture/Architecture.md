# Zoro-DB Architecture

A high-performance, crash-safe vector database designed for **similarity search at scale**, combining **in-memory ANN search** with **durable disk persistence**.  
The system follows proven database principles such as **Write-Ahead Logging (WAL)**, **append-only storage**, and **clear separation of concerns**.

---

## Overview

This database is built to support:

- Fast approximate nearest neighbor (ANN) search
- Durable and recoverable writes
- Predictable performance
- Clean extensibility for future indexing engines

The architecture uses **FAISS** for in-memory similarity search and a **custom disk storage engine** as the source of truth.

---

## Architecture Diagram

![Architecture](block-diagram.jpg)

---

## Core Components

### 1. Client Library

A Python client library that simplifies interaction with the database.

**Responsibilities**

- Communicates with the REST API / CLI
- Performs early input validation
- Supports embedding generation integration
- Handles retries and failure scenarios

**Benefits**

- Faster feedback for invalid inputs
- Reduced load on API layer
- Improved developer experience

---

### 2. API Layer (REST API / CLI)

The primary external interface for users.

**Responsibilities**

- Accepts and returns JSON data
- Performs first-level input validation
- Routes requests to internal services

**Implementation**

- Written in **Go (Golang)** for performance and concurrency
- Interacts with C++ core components via a **C API bridge**

---

### 3. Services Layer

Acts as a business-logic boundary between the API and the core database engine.

**Responsibilities**

- Final and strict input validation
- Enforces system rules and constraints
- Orchestrates calls to the Collection Manager
- Converts internal responses into API-friendly formats

---

### 4. Collection Manager

The central orchestrator of the system.

**Responsibilities**

- Manages all collection-level operations
- Coordinates WAL, disk storage, and indexing
- Handles search and indexing requests
- Ensures correct write ordering

**Key Guarantee**

> No data is indexed or exposed until it is safely logged and persisted.

---

### 5. Write-Ahead Log (WAL)

Ensures durability and crash recovery.

**Design**

- Append-only binary log files
- Every write operation is recorded before disk persistence

**Responsibilities**

- Guarantees no acknowledged write is lost
- Supports replay during crash recovery
- Prevents partial or corrupted writes

---

### 6. Disk Storage Layer

Optimized for sequential writes and efficient reads.

#### 6.1 Catalog Manager

- Tracks collection creation and deletion
- Stores metadata such as:
  - Collection ID
  - Vector dimension
  - Distance metric
  - Creation timestamp
  - Collection state
- Serves as the source of truth for collection existence

---

#### 6.2 Collection Metadata Manager

- Tracks collection-level statistics:
  - Shard count
  - Point count
  - Internal states and counters
- Used for validation and monitoring

---

#### 6.3 Index Files

- Map logical point IDs to physical storage
- Store:
  - Payload offsets
  - Payload sizes
  - Active / deleted status
- Updated in-place (not append-only)
- Currently supports **binary search traversal**
- Designed to evolve into B-tree or advanced index structures

---

#### 6.4 Source Files

- Store actual payload data
- Append-only binary format for fast writes
- No random traversal
- Data retrieval uses offset and length from index files

---

### 7. Index & Search Layer

Maintains synchronization between disk storage and in-memory indexes.

**Responsibilities**

- Keeps FAISS index consistent with disk state
- Handles insertions, deletions, and searches
- Manages point ID ↔ FAISS internal ID mapping

**Design Principle**

> Disk is the source of truth, FAISS is the accelerator.

---

### 8. FAISS (In-Memory ANN Engine)

FAISS powers the core similarity search functionality.

**Features**

- Highly optimized ANN search
- Supports multiple distance metrics
- Extremely low-latency queries

**Design Choice**

- FAISS is used for predictable performance and maturity
- HNSW is considered as a future pluggable alternative

References:

- https://github.com/facebookresearch/faiss
- https://github.com/nmslib/hnswlib

---

## Design Principles

- Write-Ahead Logging for durability
- Append-only storage for fast writes
- Disk as the source of truth
- In-memory indexing for speed
- Clear separation of responsibilities
- Crash-safe and recoverable design
- Extensible ANN backend

---

## Current Status

- Core architecture implemented
- FAISS-based in-memory search
- WAL-backed durable writes
- Custom disk storage engine
- Binary search–based index traversal

---

## Future Improvements

- Pluggable ANN engines (HNSW, DiskANN)
- Background compaction
- Sharding and replication
- Snapshot-based recovery
- Query planning optimizations

---

## Disclaimer

This project is a learning-focused implementation inspired by real-world database systems.  
It is not intended to be a drop-in replacement for production-grade vector databases.

---

## Author

**Rajath Shettigar**  
Backend / Systems / Vector Databases
