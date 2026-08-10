# physics-lab

Monorepo for physics engine experiments (rigid body, constraints, fluids, networked
physics) in C++/OpenGL, Windows-targeted.

## Build

Full toolchain setup, architecture, and rationale: see `ball-sim-v2-workflow.md`.

### Quick Start

```powershell
# Clean build directory (PowerShell)
Remove-Item -Recurse -Force build

# Configure and compile
cmake --preset msvc-debug
cmake --build --preset msvc-debug

# Run the simulation
./build/msvc-debug/bin/ball-sim.exe

[ ] TODO: Create ball_sim::App wrapper class in apps/ball-sim/. Goal: Own and drive the update loop, input handling, frame timing, and render calls.
[ ] TODO: Refactor main.cpp into a 5-line entry point that instantiates and executes App::run().