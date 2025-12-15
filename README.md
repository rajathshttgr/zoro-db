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

## Getting Started with Docker

### Start the REST API Server

Launch the Zoro-DB REST API with persistent local storage:

```bash
docker pull ghcr.io/rajathshttgr/zoro-db:dev
docker run --pull=always -d -p 6464:6464 -v $(pwd)/storage:/storage ghcr.io/rajathshttgr/zoro-db:dev
```

Access the API at `http://localhost:6464`

### Use the CLI (Optional)

For development and debugging, run the CLI tool:

```bash
docker run -it ghcr.io/rajathshttgr/zoro-db:dev /app/zoro-db
```
