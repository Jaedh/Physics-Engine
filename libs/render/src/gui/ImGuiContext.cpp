#include "render/gui/ImGuiContext.h"
#include "render/gui/ImGuiPanel.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include "core/utils/Logger.h"

namespace render {

ImGuiContext::ImGuiContext(GLFWwindow* window) {
    if (!window) {
        LOG_ERROR("ImGuiContext received nullptr window handle!");
        return;
    }

    LOG_INFO("Initializing ImGui Context and GLFW/OpenGL3 backends...");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    m_initialized = true;
}

ImGuiContext::~ImGuiContext() {
    if (!m_initialized) return;

    LOG_INFO("Shutting down ImGui Context...");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiContext::beginFrame() const {
    if (!m_initialized) return;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiContext::renderPanels() const {
    if (!m_initialized) return;
    for (const auto& panel : m_panels) {
        if (panel) {
            panel->draw();
        }
    }
}

void ImGuiContext::endFrame() const {
    if (!m_initialized) return;
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiContext::update() {
    beginFrame();
    renderPanels();
    endFrame();
}

void ImGuiContext::addPanel(std::shared_ptr<ImGuiPanel> panel) {
    m_panels.push_back(std::move(panel));
}

} // namespace render