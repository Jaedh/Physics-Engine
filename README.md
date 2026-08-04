# physics-lab

Monorepo for physics engine experiments (rigid body, constraints, fluids, networked
physics) in C++/OpenGL, Windows-targeted.

## Build

Full toolchain setup, architecture, and rationale: see `ball-sim-v2-workflow.md`.

Quick start:

    cmake --preset msvc-debug
    cmake --build --preset msvc-debug
    ./build/msvc-debug/bin/ball-sim.exe

## Layout

- `core/`   — physics math/integration/collision, engine-agnostic, no render deps
- `render/` — GLFW/OpenGL rendering layer, reusable across future engines
- `apps/`   — one subfolder per executable (currently: `ball-sim`)
- `ipc/`    — reserved for future inter-process (DDS) messaging, empty until needed