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

void World::step(std::vector<core::Ball>& m_balls, float aspectRatio) {
    const glm::vec2 gravityVector = m_gravity_dir * m_gravity_mag;

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
        physics::Collision::resolveAABB(m_balls[i], aspectRatio);

        // Circle-to-Circle collision
        for (size_t j = i + 1; j < m_balls.size(); ++j) {
            physics::Collision::resolveCircleToCircle(m_balls[i], m_balls[j]);
        }
    }
}

void World::applyImpulseToAll(std::vector<core::Ball>& m_balls, const glm::vec2& impulse) {
    for (auto& ball : m_balls) {
        if (!ball.is_static) {
            ball.velocity += impulse * ball.inv_mass;
        }
    }
}

void World::setGravityDirection(const glm::vec2& direction) { 
    m_gravity_dir = direction; 
}

void World::setGravityMagnitude(float magnitude){ 
    m_gravity_mag = magnitude; 
}

glm::vec2 World::getGravityDirection() const { 
    return m_gravity_dir; 
}


float World::getGravityMagnitude() const {
    return m_gravity_mag;
}

} // namespace ball_sim