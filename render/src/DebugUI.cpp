#include "render/DebugUI.h"
#include "render/Window.h"
#include "core/World.h"

namespace render {

DebugUI::DebugUI(const Window& window) {
    // Context initialization for ImGui using window.getNativeWindow()
}

DebugUI::~DebugUI() {
    // ImGui cleanup
}

void DebugUI::beginFrame() {}

void DebugUI::renderPanel(core::World& world) {
    // Custom ImGui sliders bound to core::World simulation parameters
}

void DebugUI::endFrame() {}

} // namespace render