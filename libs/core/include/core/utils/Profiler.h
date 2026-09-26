#ifndef CORE_UTIL_PROFILER_H
#define CORE_UTIL_PROFILER_H

#include <chrono>

namespace core::util {

class Profiler {
private:
    float m_frameTimeMs{0.0f};
    float m_fps{0.0f};

public:
    static Profiler& instance() {
        static Profiler instance;
        return instance;
    }

    void update(float deltaTimeSeconds) {
        m_frameTimeMs = deltaTimeSeconds * 1000.0f;
        m_fps = (deltaTimeSeconds > 0.0f) ? (1.0f / deltaTimeSeconds) : 0.0f;
    }

    float getFrameTimeMs() const { return m_frameTimeMs; }
    float getFps() const { return m_fps; }
};

} // namespace core::util

#endif // CORE_UTIL_PROFILER_H