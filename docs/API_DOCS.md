# Zoro DB – API Documentations

**Note:** Some API endpoints documented here are still under development and may not be available yet. For stable functionality, please use the CLI and refer to [README.md](../README.md).

Base URL:

```
http://localhost:6464
```

All requests and responses use **JSON** unless stated otherwise.

---

## Collections API

### Create Collection

Create a new vector collection.

**Endpoint**

```
POST /collections
```

**Request Body**

```json
{
  "collection_name": "products",
  "dimension": 1536,
  "distance": "cosine"
}
```

**Response**

```json
{
  "result": {
    "status": "active",
    "collection_name": "products",
    "dimension": 1536,
    "distance": "cosine",
    "sharding": 1
  },
  "time": 4.223004
}
```

---

### Delete Collection

Delete an existing collection.

**Endpoint**

```
DELETE /collections/{collection_name}
```

**Response**

```json
{
  "result": {
    "status": "deleted",
    "collection_name": "products"
  },
  "time": 2.176595
}
```

---

### List Collections

List all collections.

**Endpoint**

```
GET /collections
```

**Response**

```json
{
  "collections_count": 2,
  "collections": [
      {
        "collection_name": "products",
        "distance": "cosine",
        "dimension" 1536,
        "point_count": 10,
        "status": "Active"
      },
      {
        "collection_name": "movies",
        "distance": "dot",
        "dimension" 1536,
        "point_count": 10,
        "status": "Active"
      }
  ],
  "time": 5.539202
}
```

---

### Get Collection Info

Get metadata of a collection.

**Endpoint**

```
GET /collections/{collection_name}
```

**Response**

```json
{
  "result": {
    "coll_id": 100,
    "collection_name": "products",
    "dimension": 156,
    "distance": "cosine",
    "shards_count": 1,
    "points_count": 10,
    "status": "active"
  },
  "time": 5.539202
}
```

---

## Points API

### Upsert Points

Insert or update points in a collection.

**Endpoint**

```
POST /collections/{collection_name}/points
```

**Request Body**

```json
{
  "points": [
    {
      "id": "p1",
      "vector": [0.12, 0.98, 0.33],
      "payload": {
        "category": "electronics"
      }
    }
  ]
}
```

**Response**

```json
{
  "status": "success",
  "upserted": 1
}
```

---

### Delete Points

Delete points by ID.

**Endpoint**

```
DELETE /collections/{collection_name}/points
```

**Request Body**

```json
{
  "ids": ["p1", "p2"]
}
```

**Response**

```json
{
  "status": "success",
  "deleted": 2
}
```

---

### Count Points

Count total points in a collection.

**Endpoint**

```
GET /collections/{collection_name}/points/count
```

**Response**

```json
{
  "count": 12450
}
```

---

### Search Points

Search for similar vectors.

**Endpoint**

```
POST /collections/{collection_name}/points/search
```

**Request Body**

```json
{
  "vector": [0.11, 0.97, 0.3],
  "limit": 5
}
```

**Response**

```json
{
  "results": [
    {
      "id": "p123",
      "score": 0.92,
      "payload": {
        "category": "electronics"
      }
    }
  ]
}
```

---

## System API

### Ping

Check if server is alive.

**Endpoint**

```
GET /ping
```

**Response**

```json
{
  "status": "ok"
}
```

---

### Health Check

Run system diagnostics.

**Endpoint**

```
GET /health
```

**Response**

```json
{
  "status": "healthy",
  "uptime": "2h13m",
  "version": "0.1.0"
}
```

---

## Meta

### Version

Get server version.

**Endpoint**

```
GET /version
```

**Response**

```json
{
  "version": "0.1.0"
}
```
