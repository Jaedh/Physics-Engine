#include "World.h"
#include <physics/integration/Integrator.h>
#include <physics/collision/Collision.h>

namespace ball_sim {

void World::step(float deltaTime) {
    const glm::vec2 gravityVector{0.0f, m_gravity};

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

void World::addBall(const core::Ball& ball) { 
    m_balls.push_back(ball);
}

const std::vector<core::Ball>& World::getBalls() const { 
    return m_balls; 
}

std::vector<core::Ball>& World::getBalls() { 
    return m_balls; 
}

}