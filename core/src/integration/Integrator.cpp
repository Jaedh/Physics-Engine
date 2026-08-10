#include "core/integration/Integrator.h"

namespace core {

void Integrator::integrateSymplecticEuler(Ball& ball, const glm::vec2& gravity, float deltaTime) {
    if (ball.is_static) return;

    glm::vec2 currentAcceleration = ball.acceleration + gravity;
    ball.velocity += currentAcceleration * deltaTime;
    ball.position += ball.velocity * deltaTime;
}

} // namespace core