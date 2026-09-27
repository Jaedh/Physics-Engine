#ifndef CORE_UTIL_PROFILER_H
#define CORE_UTIL_PROFILER_H

#include <chrono>
#include <string_view>
#include <cstddef>
#include <array>
#include <algorithm>
#include <numeric>

namespace core::util {

class Profiler {
private:
    static constexpr size_t kSampleCount = 120; // 2-second history window at 60 FPS

    // Raw and Smoothed Frame Timings
    float m_rawFrameTimeMs{0.0f};
    float m_rawFps{0.0f};
    float m_smoothedFrameTimeMs{0.0f};
    float m_smoothedFps{0.0f};
    float m_smoothingFactor{0.1f}; // Exponential Moving Average alpha factor

    // Pipeline Stage Timings (in milliseconds)
    float m_physicsTimeMs{0.0f};
    float m_renderTimeMs{0.0f};

    // Rolling History & Statistical Metrics
    std::array<float, kSampleCount> m_frameTimeHistory{};
    size_t m_historyIndex{0};
    bool m_historyFull{false};
    float m_onePercentLowMs{0.0f};
    float m_maxFrameTimeMs{0.0f};

    // Simulation & Entity Counters
    size_t m_entityCount{0};
    size_t m_collisionCount{0};

public:
    static Profiler& instance() {
        static Profiler instance;
        return instance;
    }

    // Call once per frame with delta time in seconds
    void update(float deltaTimeSeconds) {
        if (deltaTimeSeconds <= 0.0f) return;

        m_rawFrameTimeMs = deltaTimeSeconds * 1000.0f;
        m_rawFps = 1.0f / deltaTimeSeconds;

        // Exponential Moving Average (EMA) smoothing for display stability
        if (m_smoothedFps == 0.0f) {
            m_smoothedFrameTimeMs = m_rawFrameTimeMs;
            m_smoothedFps = m_rawFps;
        } else {
            m_smoothedFrameTimeMs += m_smoothingFactor * (m_rawFrameTimeMs - m_smoothedFrameTimeMs);
            m_smoothedFps += m_smoothingFactor * (m_rawFps - m_smoothedFps);
        }

        // Record history for statistical breakdown
        recordFrameTimeSample(m_rawFrameTimeMs);
    }

    // Stage Timings & Metrics Setters
    void setPhysicsTimeMs(float ms) { m_physicsTimeMs = ms; }
    void setRenderTimeMs(float ms) { m_renderTimeMs = ms; }
    void setEntityCount(size_t count) { m_entityCount = count; }
    void setCollisionCount(size_t count) { m_collisionCount = count; }
    void setSmoothingFactor(float factor) { m_smoothingFactor = factor; }

    // Smoothed Display Getters
    float getFps() const { return m_smoothedFps; }
    float getFrameTimeMs() const { return m_smoothedFrameTimeMs; }

    // Statistical & Raw Getters
    float getRawFps() const { return m_rawFps; }
    float getRawFrameTimeMs() const { return m_rawFrameTimeMs; }
    float get1PercentLowMs() const { return m_onePercentLowMs; }
    float getMaxFrameTimeMs() const { return m_maxFrameTimeMs; }
    float getPhysicsTimeMs() const { return m_physicsTimeMs; }
    float getRenderTimeMs() const { return m_renderTimeMs; }

    // Counters Getters
    size_t getEntityCount() const { return m_entityCount; }
    size_t getCollisionCount() const { return m_collisionCount; }

private:
    Profiler() = default;

    void recordFrameTimeSample(float frameTimeMs) {
        m_frameTimeHistory[m_historyIndex] = frameTimeMs;
        m_historyIndex = (m_historyIndex + 1) % kSampleCount;
        if (m_historyIndex == 0) m_historyFull = true;

        size_t validCount = m_historyFull ? kSampleCount : m_historyIndex;
        if (validCount == 0) return;

        // Copy active samples to calculate percentiles
        std::array<float, kSampleCount> sortedSamples = m_frameTimeHistory;
        std::sort(sortedSamples.begin(), sortedSamples.begin() + validCount);

        size_t index99 = static_cast<size_t>(validCount * 0.99f);
        m_onePercentLowMs = sortedSamples[std::min(index99, validCount - 1)];
        m_maxFrameTimeMs = sortedSamples[validCount - 1];
    }
};

} // namespace core::util

#endif // CORE_UTIL_PROFILER_H