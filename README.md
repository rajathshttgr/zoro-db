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

For instructions on persistent storage, detached mode, or other advanced options, please refer to the [Developer Guide](docs/DEVELOPER_GUIDE.md).
