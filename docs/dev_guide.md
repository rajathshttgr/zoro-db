## Building and Running Docker Locally

### 1. Build the Docker Image

Run the following command from your project root:

```bash
docker build -t zoro-db-local .
```

Verify that the binary executes successfully by checking the build logs.

### 2. Run the Container Interactively

Since this is a CLI application, start it with interactive mode:

```bash
docker run -it zoro-db-local
```

This allows you to interact with the application directly in your terminal.
