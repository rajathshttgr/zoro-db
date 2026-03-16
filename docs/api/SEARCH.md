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
