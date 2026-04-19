## Collections

## Create a Collection

Creates a new collection with the given parameters.

**Endpoint**

```
POST /collections/{collection_name}
```

**Request Body**

```json
{
  "vectors": {
    "size": 384,
    "distance": "cosine"
  }
}
```

**Response**

```json
{
  "result": true,
  "status": "ok",
  "time": 0.000512113
}
```

## Get collection details

Retrieves parameters from the specified collection.

**Endpoint**

```
GET /collections/{collection_name}
```

**Response**

```json
{
  "result": {
    "status": "active",
    "points_count": 10,
    "segments_count": 6,
    "config": {
      "name": "my_collection",
      "internal_id": "8fa3c1d2",
      "vectors": {
        "size": 384,
        "distance": "cosine"
      }
    }
  },
  "status": "ok",
  "time": 0.000169827
}
```

## Delete a Collection

Drops the specified collection and all associated data in it.

**Endpoint**

```
DELETE /collections/{collection_name}
```

**Response**

```json
{
  "result": true,
  "status": "ok",
  "time": 0.002287665
}
```

## List all Collections

Returns a list of all existing collections.

**Endpoint**

```
GET /collections
```

**Response**

```json
{
  "result": {
    "collections_count": 2,
    "collections": [
      {
        "name": "documents",
        "size": 384,
        "distance": "dot"
      },
      {
        "name": "movies",
        "size": 1536,
        "distance": "cosine"
      }
    ]
  },
  "status": "ok",
  "time": 0.000057143
}
```

## Check Collection Exists

Checks whether the specified collection exists.

**Endpoint**

```
GET /collections/{collection_name}/exists
```

**Response**

```json
{
  "result": {
    "exists": true
  },
  "status": "ok",
  "time": 0.000024784
}
```
