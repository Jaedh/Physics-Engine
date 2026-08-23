#include "physics/collision/Collision.h"
#include <algorithm>
#include <cmath>
#include <glm/geometric.hpp>

namespace physics {

void Collision::resolveAABB(core::Ball& ball, float minBound, float maxBound) {
    const float minX = minBound + ball.radius;
    const float maxX = maxBound - ball.radius;
    const float minY = minBound + ball.radius;
    const float maxY = maxBound - ball.radius;

    if (ball.position.x < minX || ball.position.x > maxX) {
        ball.position.x = std::clamp(ball.position.x, minX, maxX);
        ball.velocity.x = -ball.velocity.x * ball.restitution;
        ball.velocity.y *= (1.0f - ball.friction);
    }

    if (ball.position.y < minY || ball.position.y > maxY) {
        ball.position.y = std::clamp(ball.position.y, minY, maxY);
        ball.velocity.y = -ball.velocity.y * ball.restitution;
        ball.velocity.x *= (1.0f - ball.friction);
    }
}

void Collision::resolveCircleToCircle(core::Ball& a, core::Ball& b) {
    glm::vec2 delta = b.position - a.position;
    float distSq = delta.x * delta.x + delta.y * delta.y;
    float radiusSum = a.radius + b.radius;

    if (distSq >= radiusSum * radiusSum || distSq == 0.0f) return;

    float distance = std::sqrt(distSq);
    glm::vec2 normal = delta / distance;
    float overlap = radiusSum - distance;

    // Use inv_mass ratio for non-static objects (inv_mass == 0 for static objects)
    float totalInvMass = a.inv_mass + b.inv_mass;
    if (totalInvMass == 0.0f) return;

    // 1. Positional separation weighted by inverse mass
    a.position -= normal * (overlap * (a.inv_mass / totalInvMass));
    b.position += normal * (overlap * (b.inv_mass / totalInvMass));

    // 2. Velocity resolution along collision normal
    glm::vec2 relativeVelocity = b.velocity - a.velocity;
    float velAlongNormal = glm::dot(relativeVelocity, normal);

    if (velAlongNormal > 0.0f) return; // Moving apart already

    float restitution = std::min(a.restitution, b.restitution);
    float impulseMagnitude = -(1.0f + restitution) * velAlongNormal / totalInvMass;

    a.velocity -= normal * (impulseMagnitude * a.inv_mass);
    b.velocity += normal * (impulseMagnitude * b.inv_mass);
}

} // namespace physics