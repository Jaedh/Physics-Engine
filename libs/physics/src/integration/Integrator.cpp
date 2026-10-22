#include "physics/integration/Integrator.h"

#include "core/utils/Logger.h"

namespace physics {

// TODO: Optimisation would be to include the enegry calculations here and return thew value

void Integrator::integrateSymplecticEuler(core::Ball& ball, const glm::vec2& gravity, float deltaTime) {
    if (ball.is_static) {
        // LOG_TRACE("Skipping integration for static ball ID {}", ball.id);
        return;
    }

    glm::vec2 currentAcceleration = ball.acceleration + gravity;
    ball.velocity += currentAcceleration * deltaTime;
    ball.position += ball.velocity * deltaTime;

    // LOG_TRACE("Integrated ball ID {}: pos=({:.3f}, {:.3f}), vel=({:.3f}, {:.3f})", ball.id, ball.position.x, ball.position.y, ball.velocity.x, ball.velocity.y);
}

} // namespace physics