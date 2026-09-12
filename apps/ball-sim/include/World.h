#ifndef BALL_SIM_WORLD_H
#define BALL_SIM_WORLD_H

#include <vector>
#include "core/objects/Ball.h"

namespace ball_sim {

class World {
    private:
        float m_gravity_mag{9.8f};
        glm::vec2  m_gravity_dir{0.0f, -1.0f};
        float currentFrameTime;
        float lastFrameTime;
        float deltaTime;
    public:
        World();
        ~World() = default;

        void step(std::vector<core::Ball>& m_balls);

        void applyImpulseToAll(std::vector<core::Ball>& m_balls, const glm::vec2& impulse);
        
        void setGravityDirection(const glm::vec2& direction);
        void setGravityMagnitude(float magnitude);

        glm::vec2 getGravityDirection() const;
        float getGravityMagnitude() const;

};

} // namespace ball_sim

#endif // BALL_SIM_WORLD_H