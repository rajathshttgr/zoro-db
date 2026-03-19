# [v0.2.0] Roadmap

| Category              | Feature                  | Description                                               | Remarks |
| --------------------- | ------------------------ | --------------------------------------------------------- | ------- |
| **Data Consistency**  | WAL, Operation Lock      | Background Processing after WAL operation acknowledgement |         |
| **SDK**               | Improvement, Abstraction | Support Advanced abstraction and async client features    |         |
| **Collections**       | Data Segmentaion         | Allow segementaion in Collection for parallel processing  |         |
| **Search Operations** | Payload Caching          | Fast data Retrival, hot caching of frequent queries       |         |

# [v0.3.0] Roadmap

| Category            | Feature               | Description                                         |
| ------------------- | --------------------- | --------------------------------------------------- |
| **Filtering**       | Advanced Filters      | Support `range`, `in`, `exists` operators           |
|                     | Boolean Filters       | Add `must`, `must_not`, `should` filter logic       |
| **Data Operations** | Delete by Filter      | Delete points matching a payload filter             |
|                     | Bulk Update by Filter | Update payload fields for filtered points           |
| **Collections**     | Index Config          | Configure index parameters (e.g., HNSW, FAISS)      |
|                     | Update Collection     | Allow modifying collection configuration            |
| **Monitoring**      | Collection Stats      | Disk usage, RAM usage, deleted points, vector count |
| **Advanced**        | Distributed Mode      | Sharding and replication support                    |
|                     | Backup / Snapshots    | Snapshot collections for backup and restore         |

# TODO LIST

- [x] REST API Implimentaion
- [x] Client Library
- [x] FAISS Integration
- [ ] WAL
- [ ] Snapshots
- [ ] Hot Cache
- [ ] DB Migration
- [ ] Web Dashboard
- [ ] Distributed Access
- [ ] Distributed Computing
