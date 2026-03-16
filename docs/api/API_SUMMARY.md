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

## [COLLECTIONS APIs](./COLLECTIONS.md)

## [POINTS APIs](./POINTS.md)

## [SEARCH APIs](./SEARCH.md)

## [SYSTEM APIs](./SYSTEM.md)

## QUICK REFERENCE

<details>
  <summary>View details</summary>

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
| `DELETE` /collections/{collection_name}/points        | Delete points     |
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

</details>
