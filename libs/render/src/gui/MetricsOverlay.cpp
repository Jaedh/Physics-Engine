#include "render/gui/MetricsOverlay.h"

#include <imgui.h>
#include <GLFW/glfw3.h>

#include "core/utils/Profiler.h"
#include "core/objects/Ball.h"

namespace render {

void MetricsOverlay::draw() {
    if (!m_visible) return;

    static float displayFps = 0.0f;
    static float displayFrameMs = 0.0f;
    static float display1LowMs = 0.0f;
    static float displayMaxMs = 0.0f;
    static float lastUpdateTime = 0.0f;

    float currentTime = static_cast<float>(glfwGetTime());
    const auto& profiler = core::util::Profiler::instance();

    if (currentTime - lastUpdateTime >= 0.1f) {
        displayFps = profiler.getFps();
        displayFrameMs = profiler.getFrameTimeMs();
        display1LowMs = profiler.get1PercentLowMs();
        displayMaxMs = profiler.getMaxFrameTimeMs();
        lastUpdateTime = currentTime;
    }

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (m_isLocked) {
        windowFlags |= ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration;
        ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f), ImGuiCond_Always);
    } else {
        ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f), ImGuiCond_FirstUseEver);
    }
    ImGui::SetNextWindowBgAlpha(0.40f);

    float mainOverlayHeight = 0.0f;

    if (ImGui::Begin("Engine Metrics", nullptr, windowFlags)) {
        ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "PERFORMANCE");
        ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);
        
        if (ImGui::SmallButton(m_isLocked ? "Unlock" : " Lock ")) {
            m_isLocked = !m_isLocked;
        }

        ImGui::Separator();

        ImGui::Text("FPS:          %.1f (%.2f ms)", displayFps, displayFrameMs);
        ImGui::Text("1%% Low:       %.2f ms (%.1f FPS)", display1LowMs, display1LowMs > 0.0f ? 1000.0f / display1LowMs : 0.0f);
        ImGui::Text("Max Spike:    %.2f ms (%.1f FPS)", displayMaxMs, displayMaxMs > 0.0f ? 1000.0f / displayMaxMs : 0.0f);
        ImGui::Text("Uptime:       %.2f s", currentTime);

        ImGui::Spacing();

        if (profiler.getPhysicsTimeMs() > 0.0f || profiler.getRenderTimeMs() > 0.0f) {
            ImGui::TextColored(ImVec4(0.9f, 0.5f, 0.2f, 1.0f), "PIPELINE STAGES");
            ImGui::Separator();
            ImGui::Text("Physics Step: %.2f ms", profiler.getPhysicsTimeMs());
            ImGui::Text("Render Step:  %.2f ms", profiler.getRenderTimeMs());
            ImGui::Spacing();
        }

        ImGui::TextColored(ImVec4(0.4f, 0.9f, 0.4f, 1.0f), "WORLD STATE");
        ImGui::Separator();
        ImGui::Text("Total Balls:  %zu", profiler.getEntityCount());
        ImGui::Text("Contacts:     %zu", profiler.getCollisionCount());

        ImGui::Spacing();

        ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.3f, 1.0f), "MEMORY");
        ImGui::Separator();
        size_t memoryBytes = profiler.getEntityCount() * sizeof(core::Ball);
        ImGui::Text("Entity Mem:   %.2f KB", static_cast<float>(memoryBytes) / 1024.0f);

        ImGui::Spacing();
        ImGui::Separator();

        ImGui::Checkbox("Show Frametime Graph", &m_showGraph);

        mainOverlayHeight = ImGui::GetWindowHeight();
    }
    ImGui::End();

    if (m_showGraph) {
        static float frameTimeBuffer[100] = {};
        static int bufferOffset = 0;

        frameTimeBuffer[bufferOffset] = profiler.getRawFrameTimeMs();
        bufferOffset = (bufferOffset + 1) % 100;

        if (m_isLocked) {
            ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f + mainOverlayHeight + 10.0f), ImGuiCond_Always);
        } else {
            ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f + mainOverlayHeight + 10.0f), ImGuiCond_FirstUseEver);
        }

        ImGui::SetNextWindowBgAlpha(0.40f);

        ImGuiWindowFlags graphFlags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
        if (m_isLocked) {
            graphFlags |= ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration;
        }

        if (ImGui::Begin("Frametime Profiler Graph", &m_showGraph, graphFlags)) {
            ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "FRAMETIME HISTORY");
            ImGui::Separator();

            ImGui::PlotLines("##frametime", 
                             frameTimeBuffer, 
                             100, 
                             bufferOffset, 
                             "Frametime (ms)", 
                             0.0f, 
                             33.3f, 
                             ImVec2(220.0f, 60.0f));
        }
        ImGui::End();
    }
}

} // namespace render