# GraphVisualization Modernization Plan (Execution Edition)

This is the actionable plan to evolve this repository into a modern, extensible algorithm platform with:
- continuous ingestion of *new algorithm updates* from free APIs, and
- a premium-quality 3D exploration experience.

## A. Immediate repository fixes (Week 1)

1. Replace platform-specific timing/thread includes and calls.
2. Remove hardcoded SFML include paths in CMake and switch to target-based linking.
3. Move implementations out of heavy headers into `.cpp` where possible.
4. Replace unsafe/raw ownership with STL containers and RAII.
5. Add test harness for DFS/BFS/shortest-path correctness.

## B. Core architecture (Weeks 1-3)

Create 4 modules:
1. `graph_core` (pure algorithms + data model).
2. `graph_timeline` (step events + deterministic replay).
3. `graph_ingest` (API polling + normalization + ranking).
4. `graph_frontend` (2D SFML now, 3D client next).

### Step-event contract
Each algorithm emits typed events:
- `node_discovered`
- `edge_relaxed`
- `frontier_push`
- `frontier_pop`
- `component_closed`

This contract decouples algorithm logic from rendering and supports both 2D and 3D clients.

## C. "Latest algorithm updates" pipeline (Weeks 2-4)

Use free/low-cost APIs documented in `docs/API_SOURCES.md`.

Pipeline:
1. Poll sources on schedule.
2. Normalize records to `AlgorithmNewsItem`.
3. Deduplicate and rank.
4. Surface "new algorithm cards" in-app.
5. Allow one-click "create experiment" from a discovered algorithm item.

## D. 3D "Tony Stark" experience (Weeks 3-8)

Detailed plan in `docs/THREE_D_VISION.md`.

Implementation track:
1. Keep C++ engine for algorithm simulation.
2. Add a WebSocket/gRPC bridge to stream timeline events.
3. Build 3D UI client (React Three Fiber) with:
   - orbit/fly controls,
   - visual layers,
   - advanced effects,
   - replay/scrub timeline.

## E. Algorithm expansion backlog

Priority algorithms:
- Dijkstra, A*, Bellman-Ford, Floyd-Warshall
- Prim, Kruskal
- Tarjan/Kosaraju SCC
- Dinic / Edmonds-Karp
- Hopcroft-Karp
- Topological sort variants

Add `IAlgorithm` plugin interface:
- metadata
- parameter schema
- `run_stepwise()` generator
- validation hooks

## F. Quality gates (must-have)

1. CI matrix: Linux/macOS/Windows.
2. Unit + property tests for invariants.
3. ASan/UBSan in debug pipeline.
4. Performance budget checks (frame time + memory).
5. Replay determinism tests (same seed => same timeline hash).

## G. Concrete deliverables checklist

- [ ] `docs/ARCHITECTURE.md` with diagrams.
- [ ] `tests/` baseline with at least 20 algorithm tests.
- [ ] `graph_ingest` prototype with 2 API connectors.
- [ ] Timeline JSON schema + serializer.
- [ ] 3D client proof-of-concept with 1k nodes.
- [ ] Feature flags for 2D and 3D frontends.

## H. Non-negotiable engineering standards

- No global `using namespace std;` in headers.
- No OS-specific includes in portable modules.
- No blocking sleeps in render-critical loops.
- No raw owning pointers unless strictly justified and documented.
