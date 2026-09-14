#include "physics/integration/Integrator.h"

namespace physics {

void Integrator::integrateSymplecticEuler(core::Ball& ball, const glm::vec2& gravity, float deltaTime) {
    if (ball.is_static) return;

    glm::vec2 currentAcceleration = ball.acceleration + gravity;
    ball.velocity += currentAcceleration * deltaTime;
    ball.position += ball.velocity * deltaTime;
}

} // namespace physics