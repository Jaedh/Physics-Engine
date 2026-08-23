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

[ ] TODO: Create a Presenter.h/cpp files to contain all the rendering of the program
[ ] TODO: Move all the intialisation to App.h/cpp, there main.cpp only initalises the App
[ ] TODO: Removed the core/include/core to core/include/; do this for render as well
[ ] TODO: Rename core to physics and make a directory for general fucntions
[ ] TODO: Create a JSON phase funciton and add it to the general functions
[ ] TODO: Use JSON + JINJA files to define presents: rendring, balls, window, for the App specific (figure out how to make this light weight)
[ ] TODO: Create a JSON file with defaul phsicys parameters
[ ] TODO: 