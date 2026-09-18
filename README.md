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

## Roadmap & TODOs

### High Priority

#### Performance & Logging
* [ ] **TODO:** Add structured logging system
* [ ] **TODO:** Add performance metrics readout in a separate terminal window
* [ ] **TODO:** Hide console window on launch for Release builds (`-mwindows` / `/SUBSYSTEM:WINDOWS`)

#### Collision Optimization & Physics Core
* [ ] **TODO:** Test physical parameters (friction, restitution, mass) under high-volume entity stress tests
* [ ] **TODO:** Add broad-phase collision optimizations (e.g., Spatial Hash / Quadtree) and record latency/performance metrics in logs
* [ ] **TODO:** Add fixed time step accumulator loop to `World::step` to prevent physics tunneling at low frame rates
* [ ] **TODO:** Implement contact manifold generation for persistent contact resolution and stacking

#### Polar Coordinates
* [ ] **TODO:** Implement math and data structures for polar coordinates centered at screen midpoint
* [ ] **TODO:** Map <kbd>Shift</kbd> key to toggle gravity between Cartesian and Polar coordinate spaces

---

### Low Priority

#### Architecture & Infrastructure
* [ ] **TODO:** Refactor `libs/core` to give it a clearer, more defined responsibility
* [ ] **TODO:** Implement a JSON parse function for global utility functions
* [ ] **TODO:** Utilize JSON + Jinja templates for lightweight app presets (rendering, balls, window config)
* [ ] **TODO:** Create a default physics parameter JSON file
* [ ] **TODO:** Implement a Memory Arena / Pool Allocator for entity management to eliminate runtime heap allocations
* [ ] **TODO:** Add Catch2 unit test target under `tests/` for mathematical utilities and collision primitives

#### Rendering & Visualization
* [ ] **TODO:** Replace raw `glDrawArrays` per-ball draw calls with Instanced Rendering in `CircleRenderer`
* [ ] **TODO:** Render velocity vectors and collision normals as debug lines
* [ ] **TODO:** Support smooth camera pan and zoom operations via uniform transformations in `Presenter`

#### UI & Interactivity
* [ ] **TODO:** Integrate ImGui controls for adjusting gravity, restitution, and spawning balls at runtime
* [ ] **TODO:** Implement object selection, dragging, and throwing via mouse inputs
* [ ] **TODO:** Add simulation controls (pause, frame-by-frame step, speed multiplier)