#include "Presenter.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "core/utils/Logger.h"

namespace ball_sim {

Presenter::Presenter(const std::vector<float>& circleVertices)
    : m_shader(kVertexShaderSource, kFragmentShaderSource),
      m_circleRenderer(circleVertices) {
    LOG_INFO("Presenter initialized with {} vertex floats.", circleVertices.size());
}

void Presenter::presenter_step(const std::vector<core::Ball>& balls, const glm::mat4& projection) {
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);          

    if (projection == glm::mat4(0.0f)) {
        LOG_WARN("Presenter received a zero projection matrix. Skipping frame render step.");
        return;
    }

    // LOG_TRACE("Presenter rendering frame for {} ball entities.", balls.size());

    m_shader.use();
    m_shader.setMat4("uProjection", projection);

    for (const auto& ball : balls) {
        m_shader.setVec2("uOffset", ball.position);
        m_shader.setFloat("uRadius", ball.radius);
        m_shader.setVec4("uColor", ball.color);
        m_circleRenderer.draw();
    }

    // renderSimpleTimeOverlay();
}

void Presenter::renderSimpleTimeOverlay() {
    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Configure overlay position (top-left corner, 10px margin)
    ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.35f); // Semi-transparent background

    // Create a frameless, non-interactive overlay window
    ImGuiWindowFlags windowFlags = 
        ImGuiWindowFlags_NoDecoration | 
        ImGuiWindowFlags_AlwaysAutoResize | 
        ImGuiWindowFlags_NoSavedSettings | 
        ImGuiWindowFlags_NoFocusOnAppearing | 
        ImGuiWindowFlags_NoNav | 
        ImGuiWindowFlags_NoMove;

    if (ImGui::Begin("Simple Time Display", nullptr, windowFlags)) {
        float totalTime = static_cast<float>(glfwGetTime());
        float frameMs = 1000.0f / ImGui::GetIO().Framerate;

        ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "SYSTEM TIME");
        ImGui::Separator();
        ImGui::Text("Uptime:   %.2f s", totalTime);
        ImGui::Text("Frame:    %.2f ms", frameMs);
        ImGui::Text("FPS:      %.1f", ImGui::GetIO().Framerate);
    }
    ImGui::End();

    // Render ImGui draw data
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

} // namespace ball_sim