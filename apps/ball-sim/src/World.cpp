#include "World.h"

#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>

#include "physics/integration/Integrator.h"
#include "physics/collision/Collision.h"
#include "core/utils/Logger.h"

namespace ball_sim {

World::World() {
    LOG_INFO("World initialized. Default Gravity Mag: {:.2f}, Dir: ({:.1f}, {:.1f})", 
             m_gravity_mag, m_gravity_dir.x, m_gravity_dir.y);
    
    lastFrameTime = static_cast<float>(glfwGetTime());
    currentFrameTime = 0.0f;
    deltaTime = 0.0f;
}

void World::world_step(std::vector<core::Ball>& m_balls, const glm::vec2& minBounds, const glm::vec2& maxBounds) {
    const glm::vec2 gravityVector = m_gravity_dir * m_gravity_mag;

    // Calculate frame delta time in seconds
    currentFrameTime = static_cast<float>(glfwGetTime());
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    // LOG_TRACE("Stepping physics world for {} balls with dt={:.4f}s", m_balls.size(), deltaTime);

    // 1. Integration phase (Velocity & Position update)
    for (auto& ball : m_balls) {
        physics::Integrator::integrateSymplecticEuler(ball, gravityVector, deltaTime);
    }

    // 2. Collision resolution phase
    m_activeCollisions = 0; 
    for (size_t i = 0; i < m_balls.size(); ++i) {
        // Wall / Boundary collision
        physics::Collision::resolveAABB(m_balls[i], minBounds, maxBounds);

        // Circle-to-Circle collision
        for (size_t j = i + 1; j < m_balls.size(); ++j) {
            physics::Collision::resolveCircleToCircle(m_balls[i], m_balls[j]);
            m_activeCollisions++;
            // TODO: add this to the collision function not here
        }
    }
}

void World::applyImpulseToAll(std::vector<core::Ball>& m_balls, const glm::vec2& impulse) {
    LOG_DEBUG("Applying impulse ({:.2f}, {:.2f}) to all {} balls.", impulse.x, impulse.y, m_balls.size());

    for (auto& ball : m_balls) {
        if (!ball.is_static) {
            ball.velocity += impulse * ball.inv_mass;
        }
    }
}

void World::setGravityDirection(const glm::vec2& direction) { 
    m_gravity_dir = direction; 
    LOG_DEBUG("World Gravity Direction set to ({:.2f}, {:.2f})", direction.x, direction.y);
}

void World::setGravityMagnitude(float magnitude) { 
    m_gravity_mag = magnitude; 
    LOG_DEBUG("World Gravity Magnitude set to {:.2f}", magnitude);
}

glm::vec2 World::getGravityDirection() const { 
    return m_gravity_dir; 
}

float World::getGravityMagnitude() const {
    return m_gravity_mag;
}

float World::getDeltaTime() const { 
    return deltaTime;
}

 size_t World::getCollisionCount() const { 
    return m_activeCollisions; 
}

} // namespace ball_sim