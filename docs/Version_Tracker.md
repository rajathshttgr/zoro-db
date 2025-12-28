## [Current Version] v0.0.1

| Major Version | Exp Version | Date        |
| ------------- | ----------- | ----------- |
| v0.0.0        | exp/v0.0    | 16 Nov 2025 |
| v0.0.1        | exp/v1.0    | 11 Dec 2025 |
|               | exp/v1.1    | 24 Dec 2025 |
|               | exp/v1.2    | 26 Dec 2025 |
|               | exp/v1.3    |             |
| v0.0.2        | exp/v2.0    |             |

## [11 Dec 2025] v0.0.1

- `exp/v1.0` Implemented a modular design, each layer is independent, includes its own tests, and is easy to debug. Docker containerization is supported. Provides both CLI and REST API support.
- `exp/v1.1` WAL (write ahead logs), REST API for collections.
- `exp/v1.2` Module level tests for each module. Modified storage and wal interactions. storage tests are done.
- `exp/v1.3` It focuses on Points upsert and delete functionality.

## [16 Nov 2025] v0.0.0

The Zoro-DB repository was created on 20/10/2025. It remained empty until 16/11/2025, during which time I conducted passive research on how SQL databases and vector databases work.

On 16/11/2025, development of the first experimental version of Zoro-DB began. The initial focus was on understanding requirements and core functionality. However, this version was not suitable for long-term evolution or a reliable project structure, so research for a new version was started.
