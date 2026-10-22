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

cmake --preset ball-sim-release
cmake --build --preset ball-sim-release
```

## Roadmap & Work Breakdown

### Phase 1 — Engine Foundations & Input Subsystem
[ ] TODO: Refactor App constructor to initialize window dimensions, title, gravity, and scene parameters from a JSON structured config file.
[ ] **TODO:** Create a default physics parameter, key binds JSON file
[ ] **TODO:** Implement JSON + templating system for lightweight app presets (rendering, entity, window config)
[ ] TODO: Add a config/ directory containing default.json and edge-case test configs (stress_test.json, zero_gravity.json).
[ ] TODO: Add max_log_level setting to JSON configs (trace, debug, info, warn, error) to control logger verbosity at startup.
[ ] TODO: Parse command-line flags (e.g., --config <path>, --log-level debug, --width 1280) to override loaded JSON settings dynamically.


[ ] TODO: Implement InputController in core::util with dynamic Action callbacks and GLFW key-mapping.
[ ] TODO: Connect SimulationControlsOverlay directly to InputController so UI buttons and physical hotkeys invoke unified action callbacks.
[ ] TODO: Parse controller keybindings from JSON configuration files (e.g., assets/config/keybindings.json).

[ ] TODO: Separate physics components from render/domain data before contact manifold updates in libs/core.

---

### Phase 2 — Simulation Correctness & Tooling
* [ ] **TODO:** Add fixed-timestep accumulator loop and render interpolation to `World::step`
* [ ] **TODO:** Add Catch2 unit test target under `tests/` to establish regression baselines for integration and collisions
* [ ] **TODO:** Test physical parameters (friction, restitution, mass) under high-volume entity stress tests
* [ ] **TODO:** Implement debug-line rendering (velocity vectors, collision normals) to support physics debugging
* [ ] **TODO:** Implement contact manifold generation and persistent contact resolution (positional slop / stabilization to fix jitter)

---

* [ ] **TODO:** Do a gitingest re-architect

---

### Phase 3 — Performance Optimization
* [ ] **TODO:** Add broad-phase collision optimization using a Spatial Hash Grid (profile before building)
* [ ] **TODO:** Implement Instanced Rendering in `CircleRenderer` and cache shader uniform locations
* [ ] **TODO:** Implement Memory Arena / Pool Allocator for entity management (gated on profiling data)

---

### Phase 4 — Interactivity & UI Polish
* [ ] **TODO:** Integrate ImGui controls for runtime tweaks, spawning, and performance metric overlays
* [ ] **TODO:** Refactor input handling system in `App` to eliminate duplicate edge-detection logic
* [ ] **TODO:** Implement mouse object selection, dragging, and throwing
* [ ] **TODO:** Add simulation state controls (pause, single frame step, speed multiplier)
* [ ] **TODO:** Resolve gravity control key-binding strategy and implement polar coordinate gravity
* [ ] **TODO:** Add simulation gravity controls (gravity magnitude 0 - 20 ish, director, polar or cartisian toggle)
* [ ] **TODO:** Support smooth camera pan and zoom operations via uniform transformations in `Presenter`