#ifndef BALL_SIM_APP_H
#define BALL_SIM_APP_H

#include <vector>
#include <string_view>
#include <optional>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "render/Window.h"
#include "core/objects/Ball.h"
#include "World.h"
#include "Presenter.h"

namespace ball_sim {

class App {
    private:
        render::Window m_window;
        World m_world;
        Presenter m_presenter;
        std::vector<core::Ball> m_balls;

        float m_lastFrameTime{0.0f};
        float aspectRatio{1.0f};

        void initDefaultScene();
    public:
        App(int width, int height, std::string_view title);
        ~App() = default;

        App(const App&) = delete;
        App& operator=(const App&) = delete;

        void run();
        void processInput();
        void processAspectRatio();

        void addBall(const core::Ball& ball);
        void addRandomBall(
            std::optional<bool> isStatic = std::nullopt,
            std::optional<float> radius = std::nullopt,
            std::optional<glm::vec4> color = std::nullopt,
            std::optional<glm::vec2> position = std::nullopt,
            std::optional<glm::vec2> velocity = std::nullopt,
            std::optional<float> restitution = std::nullopt
        );
};

} 

#endif // BALL_SIM_APP_H