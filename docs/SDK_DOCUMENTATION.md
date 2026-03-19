# Python SDK DOCUMENTATION

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
