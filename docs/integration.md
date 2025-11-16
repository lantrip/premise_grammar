## Premise Server + Frontend Integration

This document tracks how the Rust server (`premise-server`) integrates with the React frontend and how OpenAPI types are shared via `openapi-typescript` and `openapi-react-query` ([docs](https://openapi-ts.dev/openapi-react-query/)).

### Goals

- Reuse `premise-notes` and `premise-core` logic; no duplication in API layer.
- Provide a stable HTTP API consumed by the React app.
- Generate an OpenAPI schema for type-safe frontend hooks.

### Rust server

- Crate: `premise-server` (Axum + tower-http).
- Config: `STORY_ROOT` env var (absolute path) selects the project root; server reads `<STORY_ROOT>/.premise-notes`.
- Endpoints (initial):
  - `GET /api/status` → `{ exists, initialized, stats }`
  - `GET /api/index` → `NotesIndex`
  - `GET /api/beats` → `Beat[]`
  - `GET /api/facts` → `Fact[]`
  - `GET /api/timeline` → `TimelineEvent[]`
  - `GET /api/metadata` → `NotesMetadata`
  - `GET /api/aliases` → `Record<string,string[]>`
  - `GET /api/entities` → `{ entities: string[], aliases?: Record<string,string[]> }`
  - `GET /api/entity/{name}` → `{ entity, beats[], facts[], timeline[] }`
  - `POST /api/run` → triggers extraction (prem/plain/markdown; heuristic/llm), then rebuilds index; returns `{ ok, stats }`

### OpenAPI → Frontend types

- The server will expose OpenAPI at `/openapi.json` (planned; WIP).
  - Swagger UI: `/docs`
- Frontend will run:
  - `npx openapi-typescript http://localhost:5175/openapi.json -o src/lib/api/schema.d.ts`
  - Create client via `openapi-fetch` + hooks via `openapi-react-query`.

### Frontend usage (v1)

- Use TanStack Router route loaders initially; migrate to TanStack Query hooks generated via `openapi-react-query` without API changes.
- Routes:
  - `/` dashboard (stats from `/api/index`)
  - `/beats` list (from `/api/beats`)
  - `/facts` list (from `/api/facts`)
  - `/timeline` list (from `/api/timeline`)
  - `/entities` list/detail (from `/api/entities`, client filters)
  - `/run` trigger extraction via `POST /api/run`

### Tasks

- [x] Add `premise-server` to workspace
- [x] Scaffold server and core endpoints
- [x] Add OpenAPI (utoipa) and mount `/openapi.json`, Swagger UI
- [ ] Frontend: generate TS types and hooks from OpenAPI
- [ ] Wire dashboard and lists to API
- [ ] Stream run logs (SSE/WebSocket) (nice-to-have)
