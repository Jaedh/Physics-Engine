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
cmake --preset ball-sim-debug
cmake --build --preset ball-sim-debug

# HIGH PRIORITY

# Initial performance and logging
[ ] TODO: Add logging
[ ] TODO: Add Performance metrics in a seperate terminal
[ ] TODO: Remove console that opens when .exe is run (only for the final and not the debug version)

# Better coliision:
[ ] TODO: Test friction and high volumn tests
[ ] TODO: Add optimisations for collisions detection ++; add test latency and perfromance metrics in a log

# Polar
[ ] TODO: Add calculations and dat to use polar coordinates; centered around the middle of the window 
[ ] TODO: Shift -> switches gravity between cartesian to polar


# LOW PRIORITY
[ ] TODO: Figure out what to do with core, currently feels like an 'other' library
[ ] TODO: Create a JSON phase funciton and add it to the general functions
[ ] TODO: Use JSON + JINJA files to define presents: rendring, balls, window, for the App specific (figure out how to make this light weight)
[ ] TODO: Create a JSON file with defaul physics parameters


# [ ] TODO: Removed the core/include/core to core/include/; do this for render as well
