#ifndef RENDER_METRICS_OVERLAY_H
#define RENDER_METRICS_OVERLAY_H

struct GLFWwindow;

namespace render {

class MetricsOverlay {
public:
    explicit MetricsOverlay(GLFWwindow* window);
    ~MetricsOverlay();

    MetricsOverlay(const MetricsOverlay&) = delete;
    MetricsOverlay& operator=(const MetricsOverlay&) = delete;

    MetricsOverlay(MetricsOverlay&&) noexcept = default;
    MetricsOverlay& operator=(MetricsOverlay&&) noexcept = default;

    void beginFrame() const;
    void render() const;
    void endFrame() const;
    
    void draw() const;

    void toggleVisible() { m_visible = !m_visible; }
    void setVisible(bool visible) { m_visible = visible; }
    bool isVisible() const { return m_visible; }

private:
    bool m_initialized{false};
    bool m_visible{true};};

} // namespace render

#endif // RENDER_METRICS_OVERLAY_H