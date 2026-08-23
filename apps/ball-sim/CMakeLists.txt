add_executable(ball-sim
    src/main.cpp
    src/World.cpp
    src/Presenter.cpp
)

target_include_directories(ball-sim PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ball-sim PRIVATE
    core
    render
)

install(TARGETS ball-sim RUNTIME DESTINATION bin)