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

# Window:
[ ] TODO: Better background colours, alpha,; maybe a simple background pattern 
[ ] TODO: Add a button to clear all the balls

# Re-Architect 2
[ ] TODO: Fix up the build directory ( get rid of all the useless files and folders); ideally just have bin, config, a single cmake folder, libs 
[ ] TODO: Add logging
[ ] TODO: Remove console that opens when .exe is run (only for the final and not the debug version)

# Better coliision:
[ ] TODO: Test friction and high volumn tests
[ ] TODO: Fix the build directory; remove all unrequired compile files
[ ] TODO: Add optimisations for collisions detection ++; add test latency and perfromance metrics in a log

# Polar
[ ] TODO: Add calculations and dat to use polar coordinates; centered around the middle of the window 
[ ] TODO: Shift -> switches gravity between cartesian to polar


# LOW PRIORITY
[ ] TODO: Create a JSON phase funciton and add it to the general functions
[ ] TODO: Use JSON + JINJA files to define presents: rendring, balls, window, for the App specific (figure out how to make this light weight)
[ ] TODO: Create a JSON file with defaul physics parameters


# [ ] TODO: Removed the core/include/core to core/include/; do this for render as well
