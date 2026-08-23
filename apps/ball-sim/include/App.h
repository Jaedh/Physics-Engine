#ifndef BALL_SIM_APP_H
#define BALL_SIM_APP_H

#include <vector>
#include <string_view>

#include "render/Window.h"
#include "core/objects/Ball.h"
#include "World.h"
#include "Presenter.h"

namespace ball_sim {

class App {
public:
    App(int width, int height, std::string_view title);
    ~App() = default;

    // Prevent copying
    App(const App&) = delete;
    App& operator=(const App&) = delete;

    void run();

    // Helper to spawn balls for testing
    void addRandomBall();
    void addBall(const core::Ball& ball);

private:
    render::Window m_window;
    World m_world;
    Presenter m_presenter;
    std::vector<core::Ball> m_balls;

    float m_lastFrameTime{0.0f};

    void initDefaultScene();
};

} // namespace ball_sim

#endif // BALL_SIM_APP_H