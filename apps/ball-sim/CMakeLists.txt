add_executable(ball-sim
    src/main.cpp
    src/App.cpp
    src/World.cpp
    src/Presenter.cpp
)

set_target_properties(ball-sim PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/build/bin/debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/build/bin/release"
)

target_include_directories(ball-sim PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ball-sim PRIVATE
    core
    physics
    render
)

install(TARGETS ball-sim RUNTIME DESTINATION bin)