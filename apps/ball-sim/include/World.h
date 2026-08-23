#ifndef BALL_SIM_WORLD_H
#define BALL_SIM_WORLD_H

#include "core/Ball.h"
#include <vector>

namespace ball_sim {

class World {
    private:
        std::vector<core::Ball> m_balls;
        float m_gravity{-9.81f};

    public:
        World() = default;

        void addBall(const core::Ball& ball);

        const std::vector<core::Ball>& getBalls() const;
        std::vector<core::Ball>& getBalls();

        void step(float deltaTime);
};

}

#endif 