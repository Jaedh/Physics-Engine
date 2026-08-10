#ifndef CORE_COLLISION_H
#define CORE_COLLISION_H

#include "core/Ball.h"

namespace core {

class Collision {
public:
    static void resolveAABB(Ball& ball, float minBound = -1.0f, float maxBound = 1.0f);
    static void resolveCircleToCircle(Ball& a, Ball& b);
};

} // namespace core

#endif // CORE_COLLISION_H