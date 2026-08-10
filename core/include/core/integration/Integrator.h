#ifndef CORE_INTEGRATOR_H
#define CORE_INTEGRATOR_H

#include "core/Ball.h"
#include <glm/vec2.hpp>

namespace core {

class Integrator {
public:
    static void integrateSymplecticEuler(Ball& ball, const glm::vec2& gravity, float deltaTime);
};

} // namespace core

#endif // CORE_INTEGRATOR_H