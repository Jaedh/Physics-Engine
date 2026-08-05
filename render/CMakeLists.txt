add_library(render STATIC
    src/Window.cpp
    src/Shader.cpp
    src/CircleRenderer.cpp
    src/DebugUI.cpp
)

target_include_directories(render PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(render PUBLIC
    core
    glfw
    glad::glad
    imgui::imgui
    glm::glm
)

install(DIRECTORY include/ DESTINATION include)

# Once Window.cpp / Shader.cpp / CircleRenderer.cpp exist, replace the block above with:
#
# add_library(render_gl STATIC
#     src/Window.cpp
#     src/Shader.cpp
#     src/CircleRenderer.cpp
# )
# target_include_directories(render_gl PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
# )
# target_link_libraries(render_gl PUBLIC
#     glfw
#     glad::glad
#     glm::glm
#     opengl32
# )
# install(TARGETS render_gl ARCHIVE DESTINATION lib)
# install(DIRECTORY include/ DESTINATION include)