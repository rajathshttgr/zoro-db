# ZORO — Vector Database

This is the backend server for **ZORO**, a single-node vector database implemented in Go.  
The project uses **Air** for hot-reload during development.

---

## Requirements

- Go 1.23+
- Air (live reload)

Install Air:

```bash
go install github.com/air-verse/air@latest
```

---

## Run the Server (Development)

From the `api/` folder:

```bash
air
```

Air will automatically:

- Watch file changes
- Rebuild the app
- Restart the server

---

## Run Without Air (Production)

```bash
go build -o zoro-server ./cmd/server
./zoro-server
```

---

## Project Structure

```
api/
 ├── cmd/server/main.go    # Entry point
 ├── internal/             # Core logic
 ├── .air.toml             # Air config
 ├── go.mod
 └── tmp/                  # Auto-generated (ignored)
```
