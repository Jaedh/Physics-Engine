#include "core/World.h"

namespace core {

void World::addBall(const Ball& ball) { 
    m_balls.push_back(ball);
}

void World::step(float deltaTime) {
    const glm::vec2 gravityVector{0.0f, m_gravity};

    for (auto& ball : m_balls) {
        // Skip position/velocity integration for fixed environment objects
        if (ball.is_static) continue;

        // 1. Accumulate acceleration forces (Gravity + any custom forces)
        glm::vec2 currentAcceleration = ball.acceleration + gravityVector;

        // 2. Symplectic Euler Integration (Update velocity first, then position)
        ball.velocity += currentAcceleration * deltaTime;
        ball.position += ball.velocity * deltaTime;

        // Define screen/world boundary limits
        const float minX = -1.0f + ball.radius;
        const float maxX =  1.0f - ball.radius;
        const float minY = -1.0f + ball.radius;
        const float maxY =  1.0f - ball.radius;

        // --- Horizontal Boundary Collisions (Left / Right Walls) ---
        if (ball.position.x < minX || ball.position.x > maxX) {
            ball.position.x = std::clamp(ball.position.x, minX, maxX);
            ball.velocity.x = -ball.velocity.x * ball.restitution;
            ball.velocity.y *= (1.0f - ball.friction); // Wall friction against vertical sliding
        }

        // --- Vertical Boundary Collisions (Floor / Ceiling) ---
        if (ball.position.y < minY || ball.position.y > maxY) {
            ball.position.y = std::clamp(ball.position.y, minY, maxY);
            ball.velocity.y = -ball.velocity.y * ball.restitution;
            ball.velocity.x *= (1.0f - ball.friction); // Floor/Ceiling friction against horizontal sliding
        }
    }
}
const std::vector<Ball>& World::getBalls() const { 
    return m_balls; 
}

std::vector<Ball>& World::getBalls() { 
    return m_balls; 
}

} // namespace core