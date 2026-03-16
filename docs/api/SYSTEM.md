## System

## Ping

Quick server status check

**Endpoint**

```
GET /ping
```

**Response**

```json
{
  "status": "ok"
}
```

## Health Check

Run system diagnostics.

**Endpoint**

```
GET /health
```

**Response**

```json
{
  "status": "healthy",
  "uptime": "2h13m",
  "version": "0.1.0"
}
```

## Version Info

Get server version info.

**Endpoint**

```
GET /version
```

**Response**

```json
{
  "version": "0.1.0"
}
```
