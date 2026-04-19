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
  "time": 0.000553264
}
```

## Retrieve multiple points

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
  "time": 0.000267921
}
```

## Retrieve a single point

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
  "time": 0.000667921
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
  "time": 0.000572077
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
  "time": 0.000567493
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
  "time": 0.000357921
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
  "time": 0.000657041
}
```

## Scroll Points

Returns all points. Results are sorted by {id} by default and support limit and offset parameters. Optional filters can also be applied

**Endpoint**

```
POST /collections/{collection_name}/points/scroll
```

Query parameters: `?with_payload=true&with_vector=false`

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
  "time": 0.000718921
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
  "time": 0.000163911
}
```
