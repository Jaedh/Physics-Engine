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

# HIGH PRIORITY

# Key controls
[ ] TODO: Space -> adds energy to the system
[ ] TODO: Arrows -> change the direction the balls go
[ ] TODO: Mouse click adds random ball

# Window:
[ ] TODO: Add functionaility to make the windows dynamic; chnage size
[ ] TODO: Better background colours, alpha,; maybe a simple background pattern 
[ ] TODO: Remove console that opens when .exe is run

# Better coliision:
[ ] TODO: Test friction and high volumn tests
[ ] TODO: Fix the build directory; remove all unrequired compile files
[ ] TODO: Add logging
[ ] TODO: Add optimisations for collisions detection ++; add test latency and perfromance metrics in a log
[ ] TODO: 

# Polar
[ ] TODO: Add calculations and dat to use polar coordinates; centered around the middle of the window 
[ ] TODO: Shift -> switches gravity between cartesian to polar


# LOW PRIORITY
[ ] TODO: Create a JSON phase funciton and add it to the general functions
[ ] TODO: Use JSON + JINJA files to define presents: rendring, balls, window, for the App specific (figure out how to make this light weight)
[ ] TODO: Create a JSON file with defaul physics parameters


# [ ] TODO: Removed the core/include/core to core/include/; do this for render as well
