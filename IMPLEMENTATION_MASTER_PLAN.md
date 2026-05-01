# GraphVisualization Full Implementation Master Plan

## 0) Goal and Definition of Done

Build a production-grade algorithm visualization platform with:
1. High-performance 2D visualizer (desktop) with polished UX.
2. 3D exploratory frontend for dimensional and large-graph exploration.
3. Extensible algorithm plugin system.
4. API ingestion pipeline for new algorithm/paper/repo updates.
5. Cross-platform CI, tests, profiling, and reliability guarantees.

### Final acceptance criteria
- Cross-platform build green (Linux/macOS/Windows).
- >= 40 algorithm correctness tests + property tests.
- Deterministic timeline replay with stable hash per seed.
- Sub-30ms frame time for 5k nodes in 2D mode on target machine.
- 3D client demo supports 10k nodes at interactive FPS.
- API ingestion shows latest ranked updates in-app every 24h.

---

## 1) Program timeline (12 weeks)

### Phase 1 (Weeks 1-2): Stabilization and core decoupling
**Objectives**
- Eliminate blocking/render-thread hazards.
- Establish clear module boundaries.
- Introduce baseline automated tests.

**Deliverables**
- `graph_core` static library for data model + algorithms.
- `graph_runtime` for timeline/event playback.
- `graph_sfml_ui` for rendering/input.
- CMake target-based dependency graph.
- CI skeleton with build + unit test.

**Tasks**
1. Move algorithms from header-heavy classes to `.cpp` units.
2. Replace ad-hoc memory ownership with RAII containers.
3. Replace global namespace usage in headers.
4. Add deterministic seed config and startup options.
5. Add baseline tests: DFS, BFS, cycle detection, shortest path.

**Exit criteria**
- All current visual features still work.
- Timeline updates run without sleep/thread blocking.

---

### Phase 2 (Weeks 3-4): Timeline engine + UX controls
**Objectives**
- Build unified event stream model.
- Provide scrub/play/pause/step controls.

**Deliverables**
- `TimelineEvent` schema + serializer.
- Event log panel + replay controls.
- Speed profile presets (slow, normal, fast, instant).

**Tasks**
1. Define `TimelineEvent` types and payload union.
2. Implement event queue, playback clock, reverse/seek support.
3. Add UI controls and keybind mapping.
4. Implement bookmarks and event filtering.
5. Add replay snapshot tests.

**Exit criteria**
- Same algorithm run + seed reproduces identical event sequence hash.

---

### Phase 3 (Weeks 5-6): Algorithm expansion and plugin API
**Objectives**
- Scale from a few built-ins to extensible catalog.

**Deliverables**
- `IAlgorithm` interface and registry.
- Plugin metadata + parameter schema.
- Algorithm set v1: Dijkstra, A*, Bellman-Ford, Prim, Kruskal, SCC.

**Tasks**
1. Define plugin contract (`id`, `name`, params, `run_stepwise`).
2. Add algorithm validation and error reporting layer.
3. Build algorithm picker UI + parameter forms.
4. Add tests for each algorithm and edge-case graphs.
5. Add performance benchmark harness per algorithm.

**Exit criteria**
- New algorithm can be added with no renderer modifications.

---

### Phase 4 (Weeks 7-8): Data ingestion service
**Objectives**
- Bring in latest algorithm updates from free/low-cost sources.

**Deliverables**
- `graph_ingest` service (poll, normalize, dedupe, rank).
- Connectors: arXiv + Crossref + GitHub (+ optional Semantic Scholar).
- In-app "Latest Algorithms" feed panel.

**Tasks**
1. Implement source adapters and retry/backoff.
2. Build normalized model (`AlgorithmNewsItem`).
3. Add dedupe keys (DOI/arXiv/repo URL).
4. Add relevance ranking and freshness decay.
5. Add caching and rate-limit protections.

**Exit criteria**
- Feed updates automatically and remains stable under API failures.

---

### Phase 5 (Weeks 9-10): 3D frontend proof and transport bridge
**Objectives**
- Stream timeline events to a 3D client with low latency.

**Deliverables**
- WebSocket/gRPC bridge from C++ runtime.
- 3D client PoC (React Three Fiber recommended).
- Camera controls, layer toggles, timeline playback.

**Tasks**
1. Define transport DTOs and protocol versioning.
2. Build event stream server and reconnect logic.
3. Implement 3D node/edge instancing and labels.
4. Add camera modes (orbit/fly/first-person).
5. Add profiling HUD (FPS, draw calls, memory).

**Exit criteria**
- 3D client can replay same event streams from desktop runtime.

---

### Phase 6 (Weeks 11-12): Hardening and release
**Objectives**
- Production quality, docs, and packaging.

**Deliverables**
- Full CI matrix + sanitizers + static analysis.
- Performance dashboards and regression checks.
- Developer docs + user docs + contribution guide.
- Release artifacts for desktop build.

**Tasks**
1. Add ASan/UBSan/clang-tidy/clang-format gates.
2. Add perf thresholds in CI for representative scenarios.
3. Write architecture and extension docs.
4. Final UX polish, accessibility, and theme packs.
5. Package binaries and verify install flow.

**Exit criteria**
- Release candidate passes checklist and smoke tests.

---

## 2) Work breakdown structure (WBS)

### Track A: Core Engine
- A1: Graph model redesign.
- A2: Algorithm step emitter.
- A3: Deterministic RNG + seed CLI.
- A4: Error model and status reporting.
- A5: Serialization contracts.

### Track B: Desktop UI/UX
- B1: Controls panel.
- B2: Timeline panel.
- B3: Inspector widgets.
- B4: Theme and accessibility.
- B5: Input map and presets.

### Track C: Algorithms
- C1: Traversals.
- C2: Shortest paths.
- C3: MST.
- C4: Connectivity.
- C5: Flow/matching.

### Track D: Ingestion
- D1: Source adapters.
- D2: Ranking engine.
- D3: Caching + persistence.
- D4: Feed UI integration.
- D5: Ops/monitoring.

### Track E: 3D Experience
- E1: Event transport.
- E2: Renderer architecture.
- E3: Interaction model.
- E4: Visual effects.
- E5: Performance optimization.

### Track F: Quality/DevEx
- F1: Tests.
- F2: CI/CD.
- F3: Static analysis.
- F4: Benchmarks.
- F5: Docs and onboarding.

---

## 3) Team model and ownership

Minimum team for 12-week plan:
- 1 Lead C++ engineer (core/runtime).
- 1 C++/graphics engineer (2D renderer + perf).
- 1 Frontend/WebGL engineer (3D client).
- 1 Platform engineer (CI/ingestion/devops).
- 1 QA automation engineer (test and perf harness).

If solo: extend timeline to 20-28 weeks and execute in same phase order.

---

## 4) Detailed backlog by sprint

### Sprint 1
- Core split + CMake cleanup + deterministic seed + 10 tests.

### Sprint 2
- Timeline schema + playback controls + replay hash checks.

### Sprint 3
- Plugin API + 6 major algorithms + param UI.

### Sprint 4
- Ingestion adapters + feed UI + rate-limit handling.

### Sprint 5
- 3D bridge + basic 3D client + camera controls.

### Sprint 6
- Hardening, perf tuning, docs, packaging.

---

## 5) Risk register and mitigations

1. **Performance regressions at high node count**
   - Mitigation: instancing, culling, perf CI budgets.
2. **API instability/rate limits**
   - Mitigation: cache, backoff, multi-source fallback.
3. **Cross-platform build drift**
   - Mitigation: CI matrix + pinned toolchains.
4. **Plugin API churn**
   - Mitigation: versioned interface and compatibility tests.
5. **Scope creep**
   - Mitigation: strict phase exit criteria and weekly demos.

---

## 6) Metrics and KPIs

- Time-to-first-frame.
- Frame-time p50/p95.
- Memory footprint by node count.
- Algorithm replay determinism pass rate.
- Ingestion freshness (hours since last successful poll).
- Crash-free sessions.

---

## 7) API key/onboarding plan (execution)

- arXiv: no key.
- Crossref: no key (use contact email etiquette).
- GitHub: PAT recommended for higher quota.
- Semantic Scholar: key recommended for production polling.
- Store secrets in environment variables and never commit keys.

---

## 8) Immediate next 5 implementation actions

1. Create module folders and CMake targets (`graph_core`, `graph_runtime`, `graph_sfml_ui`).
2. Add `TimelineEvent` schema and serializer.
3. Add first 10 algorithm tests.
4. Implement arXiv + GitHub ingestion adapters.
5. Draft WebSocket event DTO for 3D client bridge.
