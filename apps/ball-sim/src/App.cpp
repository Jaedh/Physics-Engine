#include "App.h"

#include <GLFW/glfw3.h>
#include <random>

#include "core/math/CircleGeometry.hpp"

namespace ball_sim {

App::App(int width, int height, std::string_view title)
    : m_window(width, height, title.data()),
      m_presenter(core::math::generateCircleVertices(0.0f, 0.0f, 1.0f, 64)) {
    
    initDefaultScene();
}

void App::initDefaultScene() {
    core::Ball ball_1;

    core::Ball ball_2;
    ball_2.position = glm::vec2(0.25f, 0.25f);
    ball_2.color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

    m_balls.push_back(ball_1);
    m_balls.push_back(ball_2);
}

void App::addBall(const core::Ball& ball) {
    m_balls.push_back(ball);
}

void App::addRandomBall() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> distPos(-0.8f, 0.8f);
    std::uniform_real_distribution<float> distVel(-1.0f, 1.0f);
    std::uniform_real_distribution<float> distColor(0.2f, 1.0f);
    std::uniform_real_distribution<float> distRadius(0.05f, 0.15f);

    core::Ball ball;
    ball.position = glm::vec2(distPos(gen), distPos(gen));
    ball.velocity = glm::vec2(distVel(gen), distVel(gen));
    ball.color = glm::vec4(distColor(gen), distColor(gen), distColor(gen), 1.0f);
    ball.radius = distRadius(gen);

    m_balls.push_back(ball);
}

void App::run() {
    if (!m_window.isValid()) return;

    while (!m_window.shouldClose()) {
        // Process Input
        m_window.processInput();

        // Step World Simulation
        m_world.step(m_balls);

        // Render Frame
        m_presenter.pres_step(m_balls);

        // Display
        m_window.swapBuffers();
        m_window.pollEvents();
    }
}

} // namespace ball_sim