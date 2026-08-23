cmake_minimum_required(VERSION 3.21)
project(physics-lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_SOURCE_DIR}/cmake/OutputLayout.cmake)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_subdirectory(core)
add_subdirectory(physics)
add_subdirectory(render)

add_subdirectory(apps/ball-sim)

# add_subdirectory(ipc)    # do not add until a second executable exists (§7 step 8)
# add_subdirectory(tests)  # do not add until Catch2 unit tests exist (§7 step 7)