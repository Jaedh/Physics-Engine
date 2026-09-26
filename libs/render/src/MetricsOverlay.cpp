#include "render/MetricsOverlay.h"
#include "core/utils/Profiler.h"
#include "core/utils/Logger.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

namespace render {

MetricsOverlay::MetricsOverlay(GLFWwindow* window) {
    if (!window) {
        LOG_ERROR("MetricsOverlay initialized with nullptr GLFWwindow handle!");
        return; 
    }

    if (ImGui::GetCurrentContext() != nullptr && ImGui::GetIO().BackendPlatformUserData != nullptr) {
        LOG_WARN("ImGui GLFW backend already initialized! Cleaning up existing backend...");
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    LOG_INFO("Initializing ImGui Metrics Overlay instance...");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    m_initialized = true; // Mark as successfully initialized
}

MetricsOverlay::~MetricsOverlay() {
    if (!m_initialized) return;

    LOG_INFO("Destroying ImGui Metrics Overlay instance...");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void MetricsOverlay::beginFrame() const {
    if (!m_initialized) return;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void MetricsOverlay::render() const {
    if (!m_initialized || !m_visible) return;

    ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.35f);

    ImGuiWindowFlags windowFlags = 
        ImGuiWindowFlags_NoDecoration | 
        ImGuiWindowFlags_AlwaysAutoResize | 
        ImGuiWindowFlags_NoSavedSettings | 
        ImGuiWindowFlags_NoFocusOnAppearing | 
        ImGuiWindowFlags_NoNav | 
        ImGuiWindowFlags_NoMove;

    if (ImGui::Begin("Metrics Overlay", nullptr, windowFlags)) {
        float uptime = static_cast<float>(glfwGetTime());
        float frameMs = core::util::Profiler::instance().getFrameTimeMs();
        float fps = core::util::Profiler::instance().getFps();

        ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "SYSTEM PERFORMANCE");
        ImGui::Separator();
        ImGui::Text("Uptime:   %.2f s", uptime);
        ImGui::Text("Frame:    %.2f ms", frameMs);
        ImGui::Text("FPS:      %.1f", fps);
    }
    ImGui::End();
}

void MetricsOverlay::endFrame() const {
    if (!m_initialized) return;

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MetricsOverlay::draw() const {
    if (!m_initialized) return;

    beginFrame();
    render();
    endFrame();
}

} // namespace render