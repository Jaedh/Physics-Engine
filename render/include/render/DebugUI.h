#ifndef RENDER_DEBUG_UI_H
#define RENDER_DEBUG_UI_H

namespace core { class World; }
namespace render { class Window; }

namespace render {

class DebugUI {
public:
    explicit DebugUI(const Window& window);
    ~DebugUI();

    DebugUI(const DebugUI&) = delete;
    DebugUI& operator=(const DebugUI&) = delete;

    void beginFrame();
    void renderPanel(core::World& world);
    void endFrame();
};

} // namespace render

#endif // RENDER_DEBUG_UI_H