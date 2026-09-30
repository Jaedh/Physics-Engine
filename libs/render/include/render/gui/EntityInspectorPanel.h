#ifndef RENDER_ENTITY_INSPECTOR_PANEL_H
#define RENDER_ENTITY_INSPECTOR_PANEL_H

#include "render/gui/ImGuiPanel.h"
#include <vector>

namespace core { class Ball; }

namespace render {

class EntityInspectorPanel : public ImGuiPanel {
public:
    EntityInspectorPanel() = default; 
    ~EntityInspectorPanel() override = default;

    void draw() override;

    // Optional: Pass/bind the entity target whenever available or in loop
    void setEntities(std::vector<core::Ball>* balls) { m_balls = balls; }

private:
    std::vector<core::Ball>* m_balls{nullptr};
    int m_selectedIndex{-1};
};

} // namespace render

#endif // RENDER_ENTITY_INSPECTOR_PANEL_H