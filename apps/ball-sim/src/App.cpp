#include "App.h"

#include <GLFW/glfw3.h>
#include <random>

#include "core/math/CircleGeometry.hpp"

namespace ball_sim {

App::App(int width, int height, std::string_view title)
    : m_window(width, height, title.data()),
      m_presenter(core::math::generateCircleVertices(0.0f, 0.0f, 1.0f, 128)) {
    
    initDefaultScene();
}

void App::initDefaultScene() {
    for(int i = 0; i < 30; ++i) {
        addRandomBall();
    }
}

void App::processInput() {
    m_window.processInput();

    // SPACE: Apply impulse to all balls
    static bool spaceWasPressed = false;
    bool spaceIsPressed = m_window.isKeyPressed(GLFW_KEY_SPACE);
    if (spaceIsPressed && !spaceWasPressed) {
        m_world.applyImpulseToAll(m_balls, glm::vec2(0.0f, 5.0f));
    }
    spaceWasPressed = spaceIsPressed;

    // UP: Change gravity direction upwards
    static bool upWasPressed = false;
    bool upIsPressed = m_window.isKeyPressed(GLFW_KEY_UP);
    if (upIsPressed && !upWasPressed) {
        m_world.setGravityDirection(glm::vec2(0.0f, 1.0f));
    }
    upWasPressed = upIsPressed;

    // DOWN: Change gravity direction downwards
    static bool downWasPressed = false;
    bool downIsPressed = m_window.isKeyPressed(GLFW_KEY_DOWN);
    if (downIsPressed && !downWasPressed) {
        m_world.setGravityDirection(glm::vec2(0.0f, -1.0f));
    }
    downWasPressed = downIsPressed;

    // LEFT: Change gravity direction left
    static bool leftWasPressed = false;
    bool leftIsPressed = m_window.isKeyPressed(GLFW_KEY_LEFT);
    if (leftIsPressed && !leftWasPressed) {
        m_world.setGravityDirection(glm::vec2(-1.0f, 0.0f));
    }
    leftWasPressed = leftIsPressed;

    // RIGHT: Change gravity direction right
    static bool rightWasPressed = false;
    bool rightIsPressed = m_window.isKeyPressed(GLFW_KEY_RIGHT);
    if (rightIsPressed && !rightWasPressed) {
        m_world.setGravityDirection(glm::vec2(1.0f, 0.0f));
    }
    rightWasPressed = rightIsPressed;

    // C: Delete all balls
    static bool cWasPressed = false;
    bool cIsPressed = m_window.isKeyPressed(GLFW_KEY_C);
    if (cIsPressed && !cWasPressed) {
        m_balls.clear();
    }
    cWasPressed = cIsPressed;

    // R: Reset the scene
    static bool rWasPressed = false;
    bool rIsPressed = m_window.isKeyPressed(GLFW_KEY_R);
    if (rIsPressed && !rWasPressed) {
        m_balls.clear();
        initDefaultScene();
    }
    rWasPressed = rIsPressed;

    // MOUSE LEFT CLICK: Spawn a new ball at the cursor position
    static bool mouseWasPressed = false;
    bool mouseIsPressed = m_window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT);

    if (mouseIsPressed && !mouseWasPressed) {
        auto [xpos, ypos] = m_window.getCursorPosition();
        glm::vec2 spawnPosition = m_window.screenToWorld(xpos, ypos);

        addRandomBall(
            /*isStatic=*/std::nullopt,
            /*radius=*/std::nullopt,
            /*color=*/std::nullopt,
            /*position=*/spawnPosition
        );
    }
    mouseWasPressed = mouseIsPressed;
}

void App::addBall(const core::Ball& ball) {
    m_balls.push_back(ball);
}

void App::addRandomBall(
    std::optional<bool> isStatic,
    std::optional<float> radius,
    std::optional<glm::vec4> color,
    std::optional<glm::vec2> position,
    std::optional<glm::vec2> velocity,
    std::optional<float> restitution
) {
    static std::mt19937 gen(std::random_device{}());
    
    std::uniform_real_distribution<float> distPos(-0.8f, 0.8f);
    std::uniform_real_distribution<float> distVel(-1.0f, 1.0f);
    std::uniform_real_distribution<float> distColor(0.2f, 1.0f);
    std::uniform_real_distribution<float> distRadius(0.05f, 0.15f);
    std::uniform_real_distribution<float> distRest(0.5f, 0.95f);

    core::Ball ball;

    ball.is_static   = isStatic.value_or(false);
    ball.mass        = ball.is_static ? 0.0f : 1.0f;
    ball.inv_mass    = ball.is_static ? 0.0f : (1.0f / ball.mass);

    ball.radius      = radius.value_or(distRadius(gen));
    ball.color       = color.value_or(glm::vec4(distColor(gen), distColor(gen), distColor(gen), 1.0f));
    ball.position    = position.value_or(glm::vec2(distPos(gen)*aspectRatio, distPos(gen)*aspectRatio));
    ball.velocity    = ball.is_static ? glm::vec2(0.0f) : velocity.value_or(glm::vec2(distVel(gen), distVel(gen)));
    ball.restitution = restitution.value_or(distRest(gen));

    addBall(ball);
}

void App::run() {
    if (!m_window.isValid()) return;

    auto [minBounds, maxBounds] = m_window.getWorldBounds();
    glm::mat4 projection = m_window.getProjectionMatrix();

    while (!m_window.shouldClose()) { 
        processInput(); 

        if (m_window.consumeResizeFlag()) {
            std::tie(minBounds, maxBounds) = m_window.getWorldBounds();
            projection = m_window.getProjectionMatrix();
        }

        m_world.world_step(m_balls, minBounds, maxBounds);
        m_presenter.presenter_step(m_balls, projection);

        m_window.swapBuffers(); 
        m_window.pollEvents();
    }
}

} // namespace ball_sim