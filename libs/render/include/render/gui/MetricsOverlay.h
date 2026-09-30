#ifndef RENDER_METRICS_OVERLAY_H
#define RENDER_METRICS_OVERLAY_H

#include "render/gui/ImGuiPanel.h"

namespace render {

class MetricsOverlay : public ImGuiPanel {
public:
    MetricsOverlay() = default;
    ~MetricsOverlay() override = default;

    void draw() override;

private:
    bool m_showGraph{true};
    bool m_isLocked{true};
};

} // namespace render

#endif // RENDER_METRICS_OVERLAY_H