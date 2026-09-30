#include "render/gui/SimulationControlsOverlay.h"

#include <imgui.h>

namespace render {

void SimulationControlsOverlay::draw() {
    if (!m_visible) return;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 topRightPos = ImVec2(viewport->WorkPos.x + viewport->WorkSize.x - 10.0f, viewport->WorkPos.y + 10.0f);

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (m_isLocked) {
        windowFlags |= ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration;
        ImGui::SetNextWindowPos(topRightPos, ImGuiCond_Always, ImVec2(1.0f, 0.0f));
    } else {
        ImGui::SetNextWindowPos(topRightPos, ImGuiCond_FirstUseEver, ImVec2(1.0f, 0.0f));
    }

    ImGui::SetNextWindowBgAlpha(0.40f);

    if (ImGui::Begin("Simulation Controls", &m_visible, windowFlags)) {
        ImGui::TextColored(ImVec4(0.9f, 0.4f, 0.8f, 1.0f), "SIMULATION CONTROLS");
        ImGui::Separator();

        static bool paused = false;
        static bool stepRequested = false;

        if (ImGui::Button(paused ? "  Play  " : " Pause ")) {
            paused = !paused;
        }

        ImGui::SameLine();
        if (ImGui::Button("Step Frame")) {
            stepRequested = true;
        }

        ImGui::SameLine();
        if (ImGui::Button("Reset World")) {
            // Signal reset
        }

        ImGui::Spacing();

        static float timeScale = 1.0f;
        ImGui::SliderFloat("Time Scale", &timeScale, 0.0f, 3.0f, "%.2fx");

        ImGui::Spacing();

        static float gravity[2] = { 0.0f, -9.81f };
        ImGui::SliderFloat2("Gravity (m/s²)", gravity, -20.0f, 20.0f, "%.1f");

        ImGui::Spacing();
        ImGui::Separator();

        if (ImGui::Button("Spawn +50 Balls")) {
            // Signal spawn
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear All")) {
            // Signal clear
        }
    }
    ImGui::End();
}

} // namespace render