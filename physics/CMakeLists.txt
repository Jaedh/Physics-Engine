add_library(physics STATIC
    src/integration/Integrator.cpp
    src/collision/Collision.cpp
)

target_include_directories(physics PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(physics PUBLIC
    core
    glm::glm
)

# install(TARGETS physics ARCHIVE DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
