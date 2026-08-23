#include "World.h"

#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>

#include "physics/integration/Integrator.h"
#include "physics/collision/Collision.h"

namespace ball_sim {

World::World(){
    lastFrameTime = static_cast<float>(glfwGetTime());
    currentFrameTime = 0.0f;
    deltaTime = 0.0f;
};

void World::step(std::vector<core::Ball>& m_balls) {
    const glm::vec2 gravityVector{0.0f, m_gravity};

    // Calculate frame delta time in seconds
    currentFrameTime = static_cast<float>(glfwGetTime());
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    // 1. Integration phase (Velocity & Position update)
    for (auto& ball : m_balls) {
        physics::Integrator::integrateSymplecticEuler(ball, gravityVector, deltaTime);
    }

    // 2. Collision resolution phase
    for (size_t i = 0; i < m_balls.size(); ++i) {
        // Wall / Boundary collision
        physics::Collision::resolveAABB(m_balls[i]);

        // Circle-to-Circle collision
        for (size_t j = i + 1; j < m_balls.size(); ++j) {
            physics::Collision::resolveCircleToCircle(m_balls[i], m_balls[j]);
        }
    }
}

} // namespace ball_sim