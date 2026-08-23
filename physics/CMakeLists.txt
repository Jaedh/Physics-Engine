add_library(core STATIC
    src/integration/Integrator.cpp
    src/collision/Collision.cpp
)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(core PUBLIC
    glm::glm
)

install(TARGETS core ARCHIVE DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
