add_executable(ball-sim
    src/main.cpp
)

target_link_libraries(ball-sim PRIVATE
    core
    render
)

install(TARGETS ball-sim RUNTIME DESTINATION bin)

# install(DIRECTORY) errors if the source directory doesn't exist yet — create
# assets/shaders/ and assets/config/ with at least a placeholder file before
# uncommenting these, or guard with if(EXISTS ...) if you want to keep them
# permanently optional:
# install(DIRECTORY assets/shaders/ DESTINATION data/ball-sim/shaders)
# install(DIRECTORY assets/config/  DESTINATION config/ball-sim)