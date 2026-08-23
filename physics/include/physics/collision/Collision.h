#ifndef PHYSICS_COLLISION_H
#define PHYSICS_COLLISION_H

#include "core/objects/Ball.h"

namespace physics {

class Collision {
    public:
        static void resolveAABB(core::Ball& ball, float minBound = -1.0f, float maxBound = 1.0f);
        static void resolveCircleToCircle(core::Ball& a, core::Ball& b);
};

} // namespace physics

#endif // PHYSICS_COLLISION_H