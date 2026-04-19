<div align="center">
  <h1>Zoro-DB</h1>
  <h3>Vector Search Engine for the next generation of AI applications</h3>
</div>

<div align="center">

![Build Status](https://img.shields.io/github/actions/workflow/status/rajathshttgr/zoro-db/docker-image.yml?branch=main&label=build&style=flat-square)
![Version](https://img.shields.io/badge/version-v0.2.0-blue?style=flat-square)
![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg?style=flat-square)

</div>

---

> [!CAUTION]
> Zoro-DB is currently in an experimental stage and may be unstable.

## Overview

**Zoro-DB** is a high-performance vector database designed for similarity search workloads. It provides a RESTfull API for managing vector collections and executing fast approximate nearest neighbor (ANN) searches.

Zoro-DB is suitable for:

- Semantic search
- Recommendation systems
- RAG (Retrieval-Augmented Generation)
- Embedding similarity / clustering

## Getting Started

## Run the REST API Server

The fastest way to start Zoro-DB is with Docker:

```bash
docker run -p 6464:6464 ghcr.io/rajathshttgr/zoro-db:dev
```

Access the API at `http://localhost:6464`

For advanced setup such as persistent storage, detached mode, and development workflows, see the [DEVELOPER_GUIDE](docs/DEVELOPER_GUIDE.md).

## Python Client Installation

Install the official Python client:

```bash
pip install zoro-client
```

## Connect to the Server

```python
from zoro_client import ZoroClient

client = ZoroClient(host="localhost", port=6464)
# or
client = ZoroClient(url="http://localhost:6464")
```

## Working with Vectors

Zoro-DB supports externally generated embeddings and direct vector storage.

Example workflow using the Python SDK:

```python
from zoro_client import VectorConfig, Distance
import numpy as np

# Create a collection
client.create_collection(
    collection_name="test",
    vector_config=VectorConfig(size=100, distance=Distance.COSINE)
)

# Generate example vectors
vectors = np.random.rand(5, 100).tolist()

payloads = [
    {"document": "LangChain integration"},
    {"document": "LlamaIndex integration"},
    {"document": "Hybrid search"},
    {"document": "Fast ANN search"},
    {"document": "Python for Machine Learning"},
]

# Insert vectors
client.upsert_points(
    collection_name="test",
    vectors=vectors,
    ids=[12, 4, 34, 23, 2],
    payloads=payloads
)

# Search
results = client.search(
    collection_name="test",
    query_vector=np.random.rand(100).tolist(),
    limit=2
)

print(results)

```

> For full SDK usage, parameters, and examples see the [SDK DOCUMENTATION](docs/SDK_DOCUMENTATION.md).

## Using the REST API

Zoro-DB provides a RESTful interface that can be used from any programming language.

### Create Collection

```bash
curl -X POST http://localhost:6464/collections/:collection_name \
  -H "Content-Type: application/json" \
  -d '{
  "vectors": {
    "size": 10,
    "distance": "Cosine"
  }
}'
```

### Upsert Points

```bash
curl -X PUT http://localhost:6464/collections/:collection_name/points \
  -H "Content-Type: application/json" \
  -d '{
  "points": [
    {
      "id": 12,
      "payload": {
        "document": "How to reset a forgotten password",
        "tag": "authentication"
      },
      "vector": [0.12, 0.34, 0.53, 0.63, 0.23, 0.91, 0.11, 0.42, 0.77, 0.08]
    },
    {
      "id": 24,
      "payload": {
        "document": "Best movies to watch on this weekend",
        "tag": "entertainment"
      },
      "vector": [0.91, 0.11, 0.42, 0.77, 0.08, 0.12, 0.34, 0.53, 0.63, 0.23]
    }
  ]
}
'
```

### Search

```bash
curl -X POST http://localhost:6464/collections/:collection_name/points/search \
  -H "Content-Type: application/json" \
  -d '{
  "vector": [0.22, 0.34, 0.53, 0.63, 0.23, 0.81, 0.11, 0.42, 0.77, 0.08],
  "limit": 2,
}'
```

**Example Response**

```json
{
  "result": [
    {
      "id": 12,
      "score": 0.86,
      "payload": {
        "document": "How to reset a forgotten password",
        "tag": "authentication"
      }
    },
    {
      "id": 28,
      "score": 0.62,
      "payload": { "document": "forgot my password", "tag": "authentication" }
    }
  ],
  "status": "ok",
  "time": 0.000094741
}
```

> For the complete list of endpoints, request schemas, and response formats see the [API DOCUMENTATION](docs/api/API_DOCUMENTATION.md).

## Contributing

Contributions, ideas, and feedback are always welcome.
If you find a bug, want to suggest a feature, or improve documentation, feel free to open an issue or submit a pull request.
For contribution guidelines and development workflow see [CONTRIBUTING.md](docs/CONTRIBUTING.md).

Thank you for your interest in Zoro-DB.
