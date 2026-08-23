#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <cstdint>

namespace core {

struct Ball {
    // Spatial & Kinematics
    glm::vec2 position{0.0f, 0.0f};
    glm::vec2 prev_position{0.0f, 0.0f};
    glm::vec2 velocity{0.0f, 0.0f};
    glm::vec2 acceleration{0.0f, 0.0f};

    // Geometry & Material Dynamics
    float radius{0.2f};
    float mass{1.0f};
    float inv_mass{1.0f};     // 0.0f if static
    float restitution{0.8f};  // Bounciness (0.0 = clay, 1.0 = superball)
    float friction{0.1f};

    // Render & Identification
    glm::vec4 color{0.2f, 0.5f, 1.0f, 1.0f};
    std::uint32_t id{0};
    bool is_static{false};
};

} // namespace core