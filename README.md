<div align="center">
  <h1>Zoro-DB</h1>
  <h3>A Vector Search Engine Built from Scratch in C++</h3>
</div>

<div align="center">

![Build Status](https://img.shields.io/github/actions/workflow/status/rajathshttgr/zoro-db/docker-image.yml?branch=main&label=build&style=flat-square)
![Version](https://img.shields.io/badge/version-v0.0.1-blue?style=flat-square)
![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg?style=flat-square)

</div>

---

## Getting Started

### Run the REST API Server

Start Zoro-DB with Docker:

```bash
docker run -p 6464:6464 ghcr.io/rajathshttgr/zoro-db:dev
```

Access the API at `http://localhost:6464`

### Use the CLI (Optional)

For development or debugging, you can also run the CLI:

```bash
docker run -it ghcr.io/rajathshttgr/zoro-db:dev /app/zoro-db
```

For instructions on persistent storage, detached mode, or other advanced options, please refer to the [DEVELOPER_GUIDE](docs/DEVELOPER_GUIDE.md).

## Usage

### Create Collection

```bash
curl -X POST http://localhost:6464/collections \
  -H "Content-Type: application/json" \
  -d '{
  "collection_name": "products",
  "dimension": 10,
  "distance": "cosine"
}'
```

### Upsert Points

```bash
curl -X POST http://localhost:6464/collections/products/points \
  -H "Content-Type: application/json" \
  -d '{
  "vectors": [
    [0.12, 0.34, 0.53, 0.63, 0.23, 0.91, 0.11, 0.42, 0.77, 0.08],
    [0.91, 0.11, 0.42, 0.77, 0.08, 0.12, 0.34, 0.53, 0.63, 0.23]
  ],
  "ids": [12, 24],
  "payload": [
    {"document": "How to reset a forgotten password"},
    {"document": "Best movies to watch this weekend"}
  ]
}'
```

### Search Query

```bash
curl -X POST http://localhost:6464/collections/products/search \
  -H "Content-Type: application/json" \
  -d '{
  "vectors": [0.16, 0.34, 0.63, 0.63, 0.23, 0.91, 0.11, 0.42, 0.77, 0.07],
  "limit": 1
}'
```

**Response:**

```json
{
  "result": [
    {
      "id": 12,
      "score": 0.86,
      "payload": { "document": "How to reset a forgotten password" }
    }
  ],
  "time": 5.539202
}
```

### Delete Points

```bash
curl -X DELETE http://localhost:6464/collections/products/points \
  -H "Content-Type: application/json" \
  -d '{"ids": [12, 24]}'
```

### Get Collection Info

```bash
curl -X GET http://localhost:6464/collections/products
```

**Response:**

```json
{
  "result": {
    "coll_id": 100,
    "collection_name": "products",
    "dimension": 10,
    "distance": "cosine",
    "shards_count": 1,
    "points_count": 10,
    "status": "active"
  },
  "time": 5.539202
}
```

### List All Collections

```bash
curl -X GET http://localhost:6464/collections
```

**Response:**

```json
{
  "collections_count": 2,
  "collections": [
    {
      "collection_name": "products",
      "distance": "cosine",
      "dimension": 156,
      "status": "active"
    },
    {
      "collection_name": "movies",
      "distance": "dot",
      "dimension": 156,
      "status": "active"
    }
  ],
  "time": 5.539202
}
```

For detailed endpoint specifications, request/response schemas, and APIs that are still evolving, see the [API DOCUMENTATION](docs/API_DOCS.md). An official client library is in progress for easier and safer integration.

## Contributing

Contributions, ideas, and feedback are always welcome. If you find a bug, have a feature request, or want to suggest improvements, please feel free to open an issue. Code contributions are also appreciated. For detailed contribution guidelines and project flow, see [CONTRIBUTING.md](docs/CONTRIBUTING.md).

Thank you for your interest in Zoro-DB.
