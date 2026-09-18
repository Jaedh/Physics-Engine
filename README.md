# physics-lab

Monorepo for physics engine experiments (rigid body, constraints, fluids, networked physics) in C++/OpenGL targeting Windows.

## Resources & Visualization

* [Architecture Diagram](https://gitdiagram.com/Jaedh/Physics-Engine)
* [Repository Ingest](https://gitingest.com/Jaedh/Physics-Engine/tree/main)

## Build

For full toolchain setup, architecture, and design rationale, see `ball-sim-v2-workflow.md`.

### Quick Start

```powershell
# Clean build directory (PowerShell)
Remove-Item -Recurse -Force -ErrorAction SilentlyContinue .build

# Configure and compile using CMake presets
cmake --preset ball-sim-debug
cmake --build --preset ball-sim-debug
```

## Roadmap & Work Breakdown

### Phase 0 — Quick Wins (Unblocked)
* [ ] **TODO:** Hide console window on launch for Release builds (`/SUBSYSTEM:WINDOWS`)
* [ ] **TODO:** Support smooth camera pan and zoom operations via uniform transformations in `Presenter`

---

### Phase 1 — Engine Foundations
* [ ] **TODO:** Implement structured logging system (required for perf metrics and testing)
* [ ] **TODO:** Clarify JSON template strategy (`inja` C++ library vs. Python build script) & implement JSON parser utility
* [ ] **TODO:** Refactor `libs/core` responsibilities (split physics components from render/domain data before contact manifold updates)

---

### Phase 2 — Simulation Correctness & Tooling
* [ ] **TODO:** Add fixed-timestep accumulator loop and render interpolation to `World::step`
* [ ] **TODO:** Add Catch2 unit test target under `tests/` to establish regression baselines for integration and collisions
* [ ] **TODO:** Test physical parameters (friction, restitution, mass) under high-volume entity stress tests
* [ ] **TODO:** Implement debug-line rendering (velocity vectors, collision normals) to support physics debugging
* [ ] **TODO:** Implement contact manifold generation and persistent contact resolution (positional slop / stabilization to fix jitter)

---

### Phase 3 — Performance Optimization
* [ ] **TODO:** Add broad-phase collision optimization using a Spatial Hash Grid (profile before building)
* [ ] **TODO:** Implement Instanced Rendering in `CircleRenderer` and cache shader uniform locations
* [ ] **TODO:** Implement Memory Arena / Pool Allocator for entity management (gated on profiling data)

---

### Phase 4 — Data-Driven Configuration
* [ ] **TODO:** Create a default physics parameter JSON file
* [ ] **TODO:** Implement JSON + templating system for lightweight app presets (rendering, entity, window config)

---

### Phase 5 — Interactivity & UI Polish
* [ ] **TODO:** Integrate ImGui controls for runtime tweaks, spawning, and performance metric overlays
* [ ] **TODO:** Refactor input handling system in `App` to eliminate duplicate edge-detection logic
* [ ] **TODO:** Implement mouse object selection, dragging, and throwing
* [ ] **TODO:** Add simulation state controls (pause, single frame step, speed multiplier)
* [ ] **TODO:** Resolve gravity control key-binding strategy and implement polar coordinate gravity space (<kbd>Shift</kbd> toggle)