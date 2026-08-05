add_library(core STATIC
    src/World.cpp
)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(core PUBLIC
    glm::glm
)

install(DIRECTORY include/ DESTINATION include)

# Once real .cpp files land in src/ (fixed-timestep accumulator, collision math —
# see the extraction rule in §2.1), replace the block above with:
#
# add_library(physics_core STATIC
#     src/<file>.cpp
# )
# target_include_directories(physics_core PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
# )
# install(TARGETS physics_core ARCHIVE DESTINATION lib)
# install(DIRECTORY include/ DESTINATION include)