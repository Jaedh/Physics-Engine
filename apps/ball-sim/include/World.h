#ifndef BALL_SIM_WORLD_H
#define BALL_SIM_WORLD_H

#include <vector>
#include "core/objects/Ball.h"

namespace ball_sim {

class World {
    private:
        float m_gravity{-9.81f};
        float currentFrameTime;
        float lastFrameTime;
        float deltaTime;
    public:
        World();
        ~World() = default;

        void step(std::vector<core::Ball>& m_balls);
};

} // namespace ball_sim

#endif // BALL_SIM_WORLD_H