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
  "collection_name": "test",
  "dimension": 1536,
  "distance": "cosine"
}
```

**Response**

```json
{
  "result": {
    "status": "active",
    "collection_name": "test",
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
    "collection_name": "test"
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
      "collection_name": "test",
      "distance": "cosine",
      "dimension": 1536,
      "status": "active"
    },
    {
      "collection_name": "movies",
      "distance": "dot",
      "dimension": 1536,
      "status": "active"
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
    "collection_name": "test",
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
  "vectors": [
    [0.12, 0.34, 0.53, 0.63, 0.23, 0.91, 0.11, 0.42, 0.77, 0.08],
    [0.91, 0.11, 0.42, 0.77, 0.08, 0.12, 0.34, 0.53, 0.63, 0.23]
  ],
  "ids": [12, 24],
  "payload": [
    { "document": "How to reset a forgotten password" },
    { "document": "Best movies to watch this weekend" }
  ]
}
```

**Response**

```json
{
  "result": {
    "status": "success",
    "collection_name": "test",
    "upserted": 2
  },
  "time": 0.543257
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
  "ids": [12, 24]
}
```

**Response**

```json
{
  "result": {
    "status": "success",
    "collection_name": "test",
    "deleted": 2
  },
  "time": 36
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
  "result": {
    "collection_name": "test",
    "points_count": 2,
    "status": "success"
  },
  "time": 0.447415
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
  "limit": 2
}
```

**Response**

```json
{
  "result": [
    {
      "id": 12,
      "score": 0.86,
      "payload": { "document": "How to reset a forgotten password" }
    },
    {
      "id": 28,
      "score": 0.62,
      "payload": { "document": "forgot my password" }
    }
  ],
  "time": 5.539202
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
