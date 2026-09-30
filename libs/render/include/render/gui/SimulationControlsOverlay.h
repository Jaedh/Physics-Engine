#ifndef RENDER_SIMULATION_CONTROLS_OVERLAY_H
#define RENDER_SIMULATION_CONTROLS_OVERLAY_H

#include "render/gui/ImGuiPanel.h"

namespace render {

class SimulationControlsOverlay : public ImGuiPanel {
public:
    SimulationControlsOverlay() = default;
    ~SimulationControlsOverlay() override = default;

    void draw() override;

private:
    bool m_isLocked{true};
};

} // namespace render

#endif // RENDER_SIMULATION_CONTROLS_OVERLAY_H