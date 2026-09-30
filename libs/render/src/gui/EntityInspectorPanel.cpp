#include "render/gui/EntityInspectorPanel.h"
#include "core/objects/Ball.h"
#include <imgui.h>

namespace render {

void EntityInspectorPanel::draw() {
    if (!m_visible) return;

    if (ImGui::Begin("Entity Inspector", &m_visible)) {
        if (!m_balls || m_balls->empty()) {
            ImGui::TextDisabled("No entities active in simulation.");
            ImGui::End();
            return;
        }

        auto& balls = *m_balls;

        // Ensure selection index stays within current bounds if entities are cleared/spawned
        if (m_selectedIndex >= static_cast<int>(balls.size())) {
            m_selectedIndex = static_cast<int>(balls.size()) - 1;
        }

        // Entity Selector
        ImGui::SliderInt("Select Ball Index", &m_selectedIndex, 0, static_cast<int>(balls.size()) - 1);

        if (m_selectedIndex >= 0 && m_selectedIndex < static_cast<int>(balls.size())) {
            auto& ball = balls[m_selectedIndex];

            ImGui::Separator();
            ImGui::Text("Ball #%d Properties", m_selectedIndex);

            ImGui::DragFloat2("Position", &ball.position.x, 0.1f);
            ImGui::DragFloat2("Velocity", &ball.velocity.x, 0.1f);
            ImGui::SliderFloat("Radius", &ball.radius, 0.1f, 5.0f);
            ImGui::SliderFloat("Mass", &ball.mass, 0.1f, 100.0f);

            if (ImGui::Button("Zero Velocity")) {
                ball.velocity = {0.0f, 0.0f};
            }
        }
    }
    ImGui::End();
}

} // namespace render