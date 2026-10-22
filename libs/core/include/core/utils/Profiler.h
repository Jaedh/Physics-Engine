#ifndef CORE_UTIL_PROFILER_H
#define CORE_UTIL_PROFILER_H

#include <algorithm>
#include <array>
#include <cstddef>
#include <vector>

namespace core::util {

class Profiler {
private:
    static constexpr size_t kSampleCount = 120; // 2-second history window at 60 FPS

    // Raw & Smoothed Timings
    float m_rawFrameTimeMs{0.0f};
    float m_rawFps{0.0f};
    float m_smoothedFrameTimeMs{0.0f};
    float m_smoothedFps{0.0f};
    float m_smoothingFactor{0.1f};

    // Stage Timings (ms)
    float m_physicsTimeMs{0.0f};
    float m_renderTimeMs{0.0f};

    // Statistical Metrics
    std::array<float, kSampleCount> m_frameTimeHistory{};
    size_t m_historyIndex{0};
    bool m_historyFull{false};
    float m_onePercentLowMs{0.0f};
    float m_maxFrameTimeMs{0.0f};

    // Simulation Counters & State Metrics
    size_t m_entityCount{0};
    size_t m_collisionCount{0};
    float m_rawSystemKineticEnergyJ{0.0f};
    float m_smoothedSystemKineticEnergyJ{0.0f};

    // Private Singleton Constructors
    Profiler() = default;
    Profiler(const Profiler&) = delete;
    Profiler& operator=(const Profiler&) = delete;

    static float applyEma(float current, float target, float alpha) {
        return (current == 0.0f) ? target : current + alpha * (target - current);
    }

    void recordFrameTimeSample(float frameTimeMs) {
        m_frameTimeHistory[m_historyIndex] = frameTimeMs;
        m_historyIndex = (m_historyIndex + 1) % kSampleCount;
        if (m_historyIndex == 0) m_historyFull = true;

        size_t validCount = m_historyFull ? kSampleCount : m_historyIndex;
        if (validCount == 0) return;

        std::vector<float> samples(m_frameTimeHistory.begin(), m_frameTimeHistory.begin() + validCount);
        std::sort(samples.begin(), samples.end());

        size_t index99 = static_cast<size_t>(validCount * 0.99f);
        m_onePercentLowMs = samples[std::min(index99, validCount - 1)];
        m_maxFrameTimeMs = samples.back();
    }

public:
    static Profiler& instance() {
        static Profiler instance;
        return instance;
    }

    void update(float deltaTimeSeconds) {
        if (deltaTimeSeconds <= 0.0f) return;

        m_rawFrameTimeMs = deltaTimeSeconds * 1000.0f;
        m_rawFps = 1.0f / deltaTimeSeconds;

        m_smoothedFrameTimeMs = applyEma(m_smoothedFrameTimeMs, m_rawFrameTimeMs, m_smoothingFactor);
        m_smoothedFps = applyEma(m_smoothedFps, m_rawFps, m_smoothingFactor);

        recordFrameTimeSample(m_rawFrameTimeMs);
    }

    // Setters
    void setPhysicsTimeMs(float ms) { m_physicsTimeMs = ms; }
    void setRenderTimeMs(float ms) { m_renderTimeMs = ms; }
    void setEntityCount(size_t count) { m_entityCount = count; }
    void setCollisionCount(size_t count) { m_collisionCount = count; }
    void setSmoothingFactor(float factor) { m_smoothingFactor = factor; }

    void setSystemKineticEnergy(float energyJoules) { 
        m_rawSystemKineticEnergyJ = energyJoules; 
        m_smoothedSystemKineticEnergyJ = applyEma(m_smoothedSystemKineticEnergyJ, energyJoules, m_smoothingFactor);
    }

    // Getters
    float getFps() const { return m_smoothedFps; }
    float getFrameTimeMs() const { return m_smoothedFrameTimeMs; }
    float getRawFps() const { return m_rawFps; }
    float getRawFrameTimeMs() const { return m_rawFrameTimeMs; }
    float get1PercentLowMs() const { return m_onePercentLowMs; }
    float getMaxFrameTimeMs() const { return m_maxFrameTimeMs; }
    float getPhysicsTimeMs() const { return m_physicsTimeMs; }
    float getRenderTimeMs() const { return m_renderTimeMs; }
    size_t getEntityCount() const { return m_entityCount; }
    size_t getCollisionCount() const { return m_collisionCount; }
    float getSystemKineticEnergy() const { return m_smoothedSystemKineticEnergyJ; }
    float getRawSystemKineticEnergy() const { return m_rawSystemKineticEnergyJ; }
};

} 

#endif