#ifndef PHYSICS_INTEGRATOR_H
#define PHYSICS_INTEGRATOR_H

#include <glm/vec2.hpp>
#include "core/objects/Ball.h"

namespace physics {

class Integrator {
public:
    static void integrateSymplecticEuler(core::Ball& ball, const glm::vec2& gravity, float deltaTime);
};

} // namespace physics

#endif // PHYSICS_INTEGRATOR_H