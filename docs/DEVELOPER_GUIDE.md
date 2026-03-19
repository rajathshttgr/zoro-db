# Deploy Zoro-DB

This guide explains how to deploy **Zoro-DB using Docker** for development and production environments.

# Quick Start

Run the REST API server:

```bash
docker run -p 6464:6464 ghcr.io/rajathshttgr/zoro-db:dev
```

Access the API:

```
http://localhost:6464
```

# Recommended Deployment

For long-running services or production environments, run Zoro-DB with:

- background execution
- persistent storage
- automatic image updates

```bash
docker run -d \
  -p 6464:6464 \
  -v $(pwd)/zoro-data:/app/data \
  --name zoro-db \
  --pull always \
  ghcr.io/rajathshttgr/zoro-db:dev
```

| Option                     | Description                 |
| -------------------------- | --------------------------- |
| `-d`                       | Run container in background |
| `-p 6464:6464`             | Expose REST API             |
| `-v ./zoro-data:/app/data` | Persist database data       |
| `--name zoro-db`           | Container name              |
| `--pull always`            | Pull latest image           |

Data will be stored locally in:

```
./zoro-data
```

# Deployment Options

## Run in Detached Mode

Run Zoro-DB as a background service.

```bash
docker run -d -p 6464:6464 --name zoro-db ghcr.io/rajathshttgr/zoro-db:dev
```

View logs:

```bash
docker logs -f zoro-db
```

## Enable Persistent Storage

Persist vectors and collections across container restarts.

```bash
docker run -d \
  -p 6464:6464 \
  -v $(pwd)/zoro-data:/app/data \
  --name zoro-db \
  ghcr.io/rajathshttgr/zoro-db:dev
```

All database files are stored in:

```
./zoro-data
```

Recommended for **production deployments**.

## Use a Custom Port

If port `6464` is already in use, map a different host port.

```bash
docker run -d \
  -p 6565:6464 \
  --name zoro-db \
  ghcr.io/rajathshttgr/zoro-db:dev
```

Access the API at:

```
http://localhost:6565
```

# Container Management

Stop the container:

```bash
docker stop zoro-db
```

Start the container:

```bash
docker start zoro-db
```

Remove the container:

```bash
docker rm zoro-db
```

List running containers:

```bash
docker ps
```

# Updating Zoro-DB

Pull the latest image:

```bash
docker pull ghcr.io/rajathshttgr/zoro-db:dev
```

If using `--pull always`, Docker automatically updates the image when starting the container.

# Production Recommendation

For most deployments, use:

```bash
docker run -d \
  -p 6464:6464 \
  -v $(pwd)/zoro-data:/app/data \
  --name zoro-db \
  --pull always \
  ghcr.io/rajathshttgr/zoro-db:dev
```

This ensures:

- persistent data
- background execution
- automatic updates

## Need Help?

If you run into any issues while deploying or running Zoro-DB, feel free to open an issue in the repository.
