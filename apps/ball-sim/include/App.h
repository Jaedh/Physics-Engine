#ifndef BALL_SIM_APP_H
#define BALL_SIM_APP_H

#include <vector>
#include <string_view>
#include <optional>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "render/Window.h"
#include "render/gui/ImGuiContext.h"
#include "render/gui/MetricsOverlay.h"
#include "render/gui/SimulationControlsOverlay.h"
// #include "render/gui/EntityInspectorPanel.h"
#include "core/objects/Ball.h"
#include "World.h"
#include "Presenter.h"

namespace ball_sim {

class App {
    private:
        render::Window m_window;
        render::ImGuiContext m_guiContext;
        std::shared_ptr<render::MetricsOverlay> m_metricsOverlay;
        std::shared_ptr<render::SimulationControlsOverlay> m_controlsOverlay;
        // std::shared_ptr<render::EntityInspectorPanel> m_entityInspectorPanel;
        World m_world;
        Presenter m_presenter;
        std::vector<core::Ball> m_balls;

        float m_lastFrameTime{0.0f};

        float m_initial_width{800.0f};
        float m_initial_height{800.0f};

        glm::vec2 m_minBounds{0.0f, 0.0f};
        glm::vec2 m_maxBounds{0.0f, 0.0f};
        glm::mat4 m_projection{1.0f};
        float m_aspectRatio{1.0f};

        void initDefaultScene();

        void processInput();
        void processWindowResize();
        void processProfiler();

        void addBall(const core::Ball& ball);
        void addRandomBall(
            std::optional<bool> isStatic = std::nullopt,
            std::optional<float> radius = std::nullopt,
            std::optional<glm::vec4> color = std::nullopt,
            std::optional<glm::vec2> position = std::nullopt,
            std::optional<glm::vec2> velocity = std::nullopt,
            std::optional<float> restitution = std::nullopt
        );
    public:
        App(int width, int height, std::string_view title);
        ~App();

        App(const App&) = delete;
        App& operator=(const App&) = delete;

        void run();

};

} 

#endif // BALL_SIM_APP_H