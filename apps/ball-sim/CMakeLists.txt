add_executable(ball-sim
    src/main.cpp
    src/App.cpp
    src/World.cpp
    src/Presenter.cpp
)

target_include_directories(ball-sim PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ball-sim PRIVATE
    core
    physics
    render
)

set_target_properties(ball-sim PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/$<LOWER_CASE:$<CONFIG>>"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin/release"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin/debug"
)

set_target_properties(ball-sim PROPERTIES
    WIN32_EXECUTABLE $<CONFIG:Release>
)

if(MSVC)
    target_link_options(ball-sim PRIVATE
        $<$<CONFIG:Release>:/ENTRY:mainCRTStartup>
    )
endif()

install(TARGETS ball-sim RUNTIME DESTINATION bin)