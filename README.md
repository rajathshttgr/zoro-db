# ZoroDB - Vector Search Engine

ZoroDB v0.0.1 is an Experimental Version of Vector Database, currently it supports single Node database interaction. Working on distributed multiple node support.

## Quick Start using Docker

1. Run Engine on Docker

```
docker pull rajathshttgr/zorodb
docker run --pull=always -d -p 8864:8864 -v /data:/data rajathshttgr/zorodb
```

2. Interact with Python Client

```
pip install @rajathshttgr/zorodb
```

```python
from @rajathshttgr/zorodb import zoro-client

client = zoro-client(host="localhost", port=8864)

collection_name="New_Collection"

# get list of collections
collections = client.get_collections()

# create collection
client.create_collection(
    collection_name=collection_name,
    vectors={size=196, distance="Cosine"}
)

# get collection info
collection_info = client.get_collection(collection_name)


# delete collection
client.delete_collection(collection_name)


# add point to collection
client.upsert(
    collection_name=collection_name,
    points=[{id=1,vector=[0.4,0.8,0.2,0.5],payload={"name": "description"}},{...}...]
)

# delete point
client.delete(
    collection_name=collection_name,
    point_ids=0
)

# check health of server
health = client.health()

# search ANN vectors
search_results = client.search(
    collection_name=collection_name,
    query_vector=[0.4,0.5,0.43,0.1],
    top=5
)
```
