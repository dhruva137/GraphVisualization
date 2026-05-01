# "Tony Stark level" 3D Visualization Vision

## Objective
Deliver an immersive, high-quality 3D graph algorithm sandbox with camera flythrough, node clusters in depth, animated edge flows, and timeline replay.

## Rendering stack options
1. **Immediate path (recommended): web-first 3D client**
   - Frontend: React + TypeScript + React Three Fiber (Three.js).
   - Backend: C++ core algorithm engine exposed through gRPC/WebSocket bridge.
2. **Native path**
   - C++ with bgfx/Ogre/Filament + ImGui tooling panels.

## 3D interaction requirements
- Orbit, pan, fly, and first-person camera modes.
- Node dragging in 3D with axis gizmos.
- Layer toggles: algorithm frontier, visited set, heuristic field, edge capacities.
- Time controls: play/pause, step, scrub, speed multiplier.

## Visual effects baseline
- PBR materials for nodes/edges.
- Instanced rendering for large node counts.
- GPU-based edge ribbons/particles for flow visualization.
- Post-processing: bloom, depth-of-field (toggle), SSAO.
- Accessibility mode: high-contrast and colorblind-safe palette.

## Data model for dimensional algorithms
Support 2D/3D/ND embeddings:
- 2D: traditional layout.
- 3D: force-directed and spectral embeddings.
- ND: project with PCA/UMAP slider to inspect movement between projections.

## Quality bar milestones
- **M1:** 10k nodes interactive at 60 FPS on mid-range GPU.
- **M2:** deterministic replay of algorithm timeline.
- **M3:** cinematic mode with annotation overlays and exportable videos.
