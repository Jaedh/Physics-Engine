#ifndef RENDER_IMGUI_CONTEXT_H
#define RENDER_IMGUI_CONTEXT_H

#include <vector>
#include <memory>

struct GLFWwindow;

namespace render {

class ImGuiPanel;

class ImGuiContext {
public:
    explicit ImGuiContext(GLFWwindow* window);
    ~ImGuiContext();

    ImGuiContext(const ImGuiContext&) = delete;
    ImGuiContext& operator=(const ImGuiContext&) = delete;

    ImGuiContext(ImGuiContext&&) noexcept = default;
    ImGuiContext& operator=(ImGuiContext&&) noexcept = default;

    void beginFrame() const;
    void renderPanels() const;
    void endFrame() const;

    void update(); // Executes full beginFrame -> renderPanels -> endFrame pipeline

    void addPanel(std::shared_ptr<ImGuiPanel> panel);

private:
    bool m_initialized{false};
    std::vector<std::shared_ptr<ImGuiPanel>> m_panels;
};

} // namespace render

#endif // RENDER_IMGUI_CONTEXT_H