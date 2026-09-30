#ifndef RENDER_IMGUI_PANEL_H
#define RENDER_IMGUI_PANEL_H

namespace render {

class ImGuiPanel {
public:
    virtual ~ImGuiPanel() = default;

    // Derived classes implement their specific ImGui widgets here
    virtual void draw() = 0;

    void setVisible(bool visible) { m_visible = visible; }
    bool isVisible() const { return m_visible; }
    void toggleVisible() { m_visible = !m_visible; }

protected:
    bool m_visible{true};
};

} // namespace render

#endif // RENDER_IMGUI_PANEL_H