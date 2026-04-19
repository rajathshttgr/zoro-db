<!--All notable changes to Zoro-DB will be documented in this file. -->

## [0.2.0] 17-Mar-2026

1. Collection API Improvement

- Drop CLI - done
- Refactor and simplify build & run entry point. - done
- Update API layer, service layer data parsing - done
- Update python client to match new API changes - done
- Update api documentaion, distance matrics to lower case - done
- collection metadata caching, fast input validations - done

2. Async data Ingestion

- Upsert points to wal (logs) and call async operation and return acknowledgment quickly
