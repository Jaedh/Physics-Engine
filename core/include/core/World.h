#ifndef CORE_WORLD_H
#define CORE_WORLD_H

#include "core/Ball.h"
#include <vector>
#include <algorithm>

namespace core {

class World {
    private:
        std::vector<Ball> m_balls;
        float m_gravity{-9.81f};
    public:
        World() = default;

        void addBall(const Ball& ball);

        const std::vector<Ball>& getBalls() const;
        std::vector<Ball>& getBalls();

        void step(float deltaTime);
};

} // namespace core

#endif // CORE_WORLD_H