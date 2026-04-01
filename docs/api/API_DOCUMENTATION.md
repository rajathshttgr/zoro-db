# Zoro DB – REST API Documentations

## How does Zoro-DB work?

1. First, you should create a collection to store all your data.
2. Then upsert data points and enrich them with a custom payload.
3. With a full collection, run a search to find relevant results.

**Base URL:**

```
http://localhost:6464
```

All requests and responses use JSON.

**Common Query Parameters:**

These parameters apply to retrieval APIs.

| Parameter      | Default | Description              |
| -------------- | ------- | ------------------------ |
| `with_payload` | `true`  | Include payload metadata |
| `with_vector`  | `false` | Include stored vector    |

Example:

```
GET /collections/docs/points/12?with_vector=true
```

## Collections

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
  "time": 0.21019
}
```

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
  "time": 0.31409
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
  "time": 0.80509
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
  "time": 0.41409
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
  "time": 0.00974
}
```

## Points

## Upsert points

Performs the insert or update action on specified points. Any point with an existing {id} will be overwritten.

**Endpoint**

```
PUT /collections/{collection_name}/points
```

**Request Body**

```json
{
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
```

**Response**

```json
{
  "result": {
    "status": "acknowledged",
    "operation_id": 1
  },
  "status": "ok",
  "time": 0.00974
}
```

## Retrieve points

Retrieves all details from multiple points.

**Endpoint**

```
POST /collections/{collection_name}/points
```

Query parameters:`?with_payload=true&with_vector=false`

**Request Body**

```json
{
  "ids": [12, 24]
}
```

**Response**

```json
{
  "result": [
    {
      "id": 12,
      "payload": {
        "document": "How to reset a forgotten password",
        "tag": "authentication"
      }
    },
    {
      "id": 24,
      "payload": {
        "document": "Best movies to watch this weekend",
        "tag": "entertainment"
      }
    }
  ],
  "status": "ok",
  "time": 0.01974
}
```

## Retrieve a point

Retrieves all details from a single point.

**Endpoint**

```
GET /collections/{collection_name}/points/{id}
```

Query parameters:
`?with_payload=true&with_vector=false`

**Response**

```json
{
  "result": {
    "id": 12,
    "payload": {
      "document": "How to reset a forgotten password",
      "tag": "authentication"
    }
  },
  "status": "ok",
  "time": 0.671502
}
```

## Delete Points

Deletes specified points from the collection.

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
    "status": "acknowledged",
    "operation_id": 2
  },
  "status": "ok",
  "time": 0.02904
}
```

## Update vectors

Updates specified vectors on points.

**Endpoint**

```
PUT /collections/{collection_name}/points/vectors
```

**Request Body**

```json
{
  "points": [
    {
      "id": 12,
      "vector": [0.23, 0.34, 0.13, 0.63, 0.93, 0.91, 0.11, 0.42, 0.77, 0.08]
    },
    {
      "id": 24,
      "vector": [0.01, 0.11, 0.32, 0.77, 0.08, 0.92, 0.34, 0.53, 0.63, 0.83]
    }
  ]
}
```

**Response**

```json
{
  "result": { "status": "completed", "operation_id": 5 },
  "status": "ok",
  "time": 0.03504
}
```

## Overwrite payload

Replaces the entire payload of a specified point with a new payload.

**Endpoint**

```
PUT /collections/{collection_name}/points/payload
```

**Request Body**

```json
{
  "points": [
    {
      "id": 12,
      "payload": {
        "document": "Reset password by clicking on forgot password"
      }
    },
    {
      "id": 24,
      "payload": {
        "document": "Best TV shows or movies to watch on this weekend"
      }
    }
  ]
}
```

**Response**

```json
{
  "result": { "status": "completed", "operation_id": 5 },
  "status": "ok",
  "time": 0.03504
}
```

## Update Payload

Update payload values (Add / Overwrite Keys) for specified points.

**Endpoint**

```
PATCH /collections/{collection_name}/points/payload
```

**Request Body**

```json
{
  "points": [
    {
      "id": 12,
      "payload": {
        "category": "security"
      }
    }
  ]
}
```

**Response**

```json
{
  "result": { "status": "completed", "operation_id": 7 },
  "status": "ok",
  "time": 0.06504
}
```

## Scroll Points

Returns all points. Results are sorted by {id} by default and support limit and offset parameters. Optional filters can also be applied

**Endpoint**

```
POST /collections/{collection_name}/points/scroll
```

Query parameters:`?with_payload=true&with_vector=false`

**Request body:**

```json
{
  "filter": {
    "key": "tag",
    "match": "authentication"
  }
}
```

Request body is optional and used only for filtering.

**Response**

```json
{
  "result": [
    {
      "id": 12,
      "payload": {
        "document": "How to reset a forgotten password",
        "tag": "authentication"
      }
    },
    {
      "id": 24,
      "payload": {
        "document": "Best movies to watch on this weekend",
        "tag": "entertainment"
      }
    }
  ],
  "status": "ok",
  "time": 0.90974
}
```

## Count Points

Counts the number of points in a specified collection.

**Endpoint**

```
GET /collections/{collection_name}/points/count
```

**Request body:**

```json
{
  "filter": {
    "key": "tag",
    "match": "authentication"
  }
}
```

Request body is optional and used only for filtering.

**Response**

```json
{
  "result": {
    "count": 2
  },
  "status": "ok",
  "time": 0.04741
}
```

## Search

## Search points

Retrieves the closest points based on vector similarity.

**Endpoint**

```
POST /collections/{collection_name}/points/search
```

Query parameters:
`?with_payload=true`

**Request Body**

```json
{
  "vector": [0.22, 0.34, 0.53, 0.63, 0.23, 0.81, 0.11, 0.42, 0.77, 0.08],
  "limit": 2,
  "score_threshold": 0.6,
  "filter": {
    "key": "tag",
    "match": "authentication"
  }
}
```

Request body filter and score threshold is optional.

**Response**

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
  "time": 0.94741
}
```

## Search batch points

Retrieves the closest points in batches based on vector similarity and given filtering conditions.

**Endpoint**

```
POST /collections/{collection_name}/points/search/batch
```

Query parameters:
`?with_payload=false`

**Request Body**

```json
{
  "searches": [
    {
      "vector": [0.22, 0.34, 0.53, 0.63, 0.23, 0.81, 0.11, 0.42, 0.77, 0.08],
      "limit": 2
    },
    {
      "vector": [0.18, 0.78, 0.53, 0.63, 0.24, 0.81, 0.12, 0.42, 0.17, 0.98],
      "limit": 1
    }
  ]
}
```

`default limit = 10, max limit = 1000`

**Response**

```json
{
  "result": [
    [
      {
        "id": 12,
        "score": 0.9942395
      },
      {
        "id": 24,
        "score": 0.33141318
      }
    ],
    [
      {
        "id": 18,
        "score": 0.93818986
      }
    ]
  ],
  "status": "ok",
  "time": 0.74741
}
```

## System

## Ping

Quick server status check

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

## Health Check

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

## Version Info

Get server version info.

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

## QUICK REFERENCE

### Collections

| End Point                                   | Description             |
| ------------------------------------------- | ----------------------- |
| `POST` /collections/{collection_name}       | Create a Collection     |
| `GET` /collections/{collection_name}        | Get collection details  |
| `DELETE` /collections/{collection_name}     | Delete a Collection     |
| `GET` /collections                          | List all Collections    |
| `GET` /collections/{collection_name}/exists | Check Collection Exists |

### Points

| End Point                                             | Description       |
| ----------------------------------------------------- | ----------------- |
| `PUT` /collections/{collection_name}/points           | Upsert points     |
| `POST` /collections/{collection_name}/points          | Retrieve points   |
| `GET` /collections/{collection_name}/points/{id}      | Retrieve a point  |
| `DELETE ` /collections/{collection_name}/points       | Delete points     |
| `PUT` /collections/{collection_name}/points/vectors   | Update vectors    |
| `PUT` /collections/{collection_name}/points/payload   | Overwrite payload |
| `PATCH` /collections/{collection_name}/points/payload | Update paload     |
| `GET` /collections/{collection_name}/points/scroll    | Scroll points     |
| `GET` /collections/{collection_name}/points/count     | Count points      |

### Search

| End Point                                                 | Description         |
| --------------------------------------------------------- | ------------------- |
| `POST` /collections/{collection_name}/points/search       | Search points       |
| `POST` /collections/{collection_name}/points/search/batch | Search batch points |

### System

| End Point      | Description  |
| -------------- | ------------ |
| `GET` /ping    | Ping         |
| `GET` /health  | Health Check |
| `GET` /version | Version Info |
