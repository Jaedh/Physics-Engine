add_library(render STATIC
    src/Window.cpp
    src/Shader.cpp
    src/CircleRenderer.cpp
)

target_include_directories(render PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# remove core from here, there should be no need to add core here
target_link_libraries(render PUBLIC
    core
    glfw
    glad::glad
    imgui::imgui
    glm::glm
)

# install(TARGETS render ARCHIVE DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)