## Building and Running Docker Locally

### Build the Docker Image

From your project root, execute:

```bash
docker build -t zoro-db .
```

Check the build logs to confirm successful compilation.

### Run the REST API

Start the container with the REST API (default for production):

```bash
docker run -p 9000:9000 zoro-db
```

### Run the CLI

For development and testing, use the CLI:

```bash
docker run -it zoro-db /app/zoro-db
```
