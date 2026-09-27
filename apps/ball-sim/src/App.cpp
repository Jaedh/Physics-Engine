#include "App.h"

#include <GLFW/glfw3.h>
#include <random>

#include "core/math/CircleGeometry.hpp"
#include "core/utils/Logger.h"
#include "core/utils/Profiler.h"
#include "render/MetricsOverlay.h"

namespace ball_sim {

    // TODO: make this file ligher somehow
    // TODO: Make this intialiser better based on a congif file
App::App(int width, int height, std::string_view title)
    : m_window(width, height, title.data()),
      m_metricsOverlay(m_window.getNativeWindow()),
      m_presenter(core::math::generateCircleVertices(0.0f, 0.0f, 1.0f, 128)) {
    
    LOG_INFO("Initializing App with window resolution {}x{} and title '{}'", width, height, title);
    
    aspectRatio = m_window.getAspectRatio();
    initDefaultScene();
    LOG_INFO("App subsystem successfully initialized.");
}

void App::initDefaultScene() {
    LOG_INFO("Initializing default scene with 30 balls...");
    for (int i = 0; i < 30; ++i) {
        addRandomBall();
    }
}

App::~App() {
    LOG_INFO("Shutting down App subsystem...");
    glfwTerminate();
}

void App::processInput() {
    m_window.processInput();

    // SPACE: Apply impulse to all balls
    static bool spaceWasPressed = false;
    bool spaceIsPressed = m_window.isKeyPressed(GLFW_KEY_SPACE);
    if (spaceIsPressed && !spaceWasPressed) {
        LOG_DEBUG("Input action: Applying vertical impulse to all balls.");
        m_world.applyImpulseToAll(m_balls, glm::vec2(0.0f, 5.0f));
    }
    spaceWasPressed = spaceIsPressed;

    // UP: Change gravity direction upwards
    static bool upWasPressed = false;
    bool upIsPressed = m_window.isKeyPressed(GLFW_KEY_UP);
    if (upIsPressed && !upWasPressed) {
        LOG_DEBUG("Input action: Gravity set to UP.");
        m_world.setGravityDirection(glm::vec2(0.0f, 1.0f));
    }
    upWasPressed = upIsPressed;

    // DOWN: Change gravity direction downwards
    static bool downWasPressed = false;
    bool downIsPressed = m_window.isKeyPressed(GLFW_KEY_DOWN);
    if (downIsPressed && !downWasPressed) {
        LOG_DEBUG("Input action: Gravity set to DOWN.");
        m_world.setGravityDirection(glm::vec2(0.0f, -1.0f));
    }
    downWasPressed = downIsPressed;

    // LEFT: Change gravity direction left
    static bool leftWasPressed = false;
    bool leftIsPressed = m_window.isKeyPressed(GLFW_KEY_LEFT);
    if (leftIsPressed && !leftWasPressed) {
        LOG_DEBUG("Input action: Gravity set to LEFT.");
        m_world.setGravityDirection(glm::vec2(-1.0f, 0.0f));
    }
    leftWasPressed = leftIsPressed;

    // RIGHT: Change gravity direction right
    static bool rightWasPressed = false;
    bool rightIsPressed = m_window.isKeyPressed(GLFW_KEY_RIGHT);
    if (rightIsPressed && !rightWasPressed) {
        LOG_DEBUG("Input action: Gravity set to RIGHT.");
        m_world.setGravityDirection(glm::vec2(1.0f, 0.0f));
    }
    rightWasPressed = rightIsPressed;

    // SHIFT: Turn off gravity (set to zero)
    static bool shiftWasPressed = false;
    bool shiftIsPressed = m_window.isKeyPressed(GLFW_KEY_LEFT_SHIFT) || m_window.isKeyPressed(GLFW_KEY_RIGHT_SHIFT);
    if (shiftIsPressed && !shiftWasPressed) {
        LOG_DEBUG("Input action: Gravity disabled (set to ZERO).");
        m_world.setGravityDirection(glm::vec2(0.0f, 0.0f));
    }
    shiftWasPressed = shiftIsPressed;

    // C: Delete all balls
    static bool cWasPressed = false;
    bool cIsPressed = m_window.isKeyPressed(GLFW_KEY_C);
    if (cIsPressed && !cWasPressed) {
        LOG_DEBUG("Input action: Clearing all entities (count: {}).", m_balls.size());
        m_balls.clear();
    }
    cWasPressed = cIsPressed;

    // R: Reset the scene
    static bool rWasPressed = false;
    bool rIsPressed = m_window.isKeyPressed(GLFW_KEY_R);
    if (rIsPressed && !rWasPressed) {
        LOG_DEBUG("Input action: Resetting scene.");
        m_balls.clear();
        initDefaultScene();
    }
    rWasPressed = rIsPressed;

    // MOUSE LEFT CLICK: Spawn a new ball at cursor position
    static bool mouseWasPressed = false;
    bool mouseIsPressed = m_window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT);

    if (mouseIsPressed && !mouseWasPressed) {
        auto [xpos, ypos] = m_window.getCursorPosition();
        glm::vec2 spawnPosition = m_window.screenToWorld(xpos, ypos);

        LOG_DEBUG("Input action: Spawning ball at screen ({:.1f}, {:.1f}) -> world ({:.3f}, {:.3f})", 
                  xpos, ypos, spawnPosition.x, spawnPosition.y);

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
    LOG_TRACE("Added new ball entity [ID: {}]. Total balls: {}", ball.id, m_balls.size());
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
    ball.position    = position.value_or(glm::vec2(distPos(gen) * aspectRatio, distPos(gen) * aspectRatio));
    ball.velocity    = ball.is_static ? glm::vec2(0.0f) : velocity.value_or(glm::vec2(distVel(gen), distVel(gen)));
    ball.restitution = restitution.value_or(distRest(gen));

    LOG_DEBUG("Constructed random ball: pos=({:.2f}, {:.2f}), radius={:.2f}, mass={:.2f}, static={}", 
              ball.position.x, ball.position.y, ball.radius, ball.mass, ball.is_static);

    addBall(ball);
}

// TODO: Offload some of the logic from the main loop to this function to keep it cleaner
void App::run() {
    if (!m_window.isValid()) {
        LOG_ERROR("Cannot run application loop: GLFW window handle is invalid.");
        return;
    }

    auto [minBounds, maxBounds] = m_window.getWorldBounds();
    glm::mat4 projection = m_window.getProjectionMatrix();

    LOG_INFO("Entering main application loop.");
    while (!m_window.shouldClose()) { 
        processInput(); 

        if (m_window.consumeResizeFlag()) {
            std::tie(minBounds, maxBounds) = m_window.getWorldBounds();
            projection = m_window.getProjectionMatrix();
            aspectRatio = m_window.getAspectRatio();
            LOG_DEBUG("Window resized. Updated bounds min=({:.2f}, {:.2f}), max=({:.2f}, {:.2f})", 
                      minBounds.x, minBounds.y, maxBounds.x, maxBounds.y);
        }

        m_world.world_step(m_balls, minBounds, maxBounds);
        // core::util::Profiler::instance().update(m_world.getDeltaTime());
        auto& profiler = core::util::Profiler::instance();
        profiler.update(m_world.getDeltaTime());
        profiler.setEntityCount(m_balls.size());
        profiler.setCollisionCount(m_world.getCollisionCount());

        m_presenter.presenter_step(m_balls, projection);
        m_metricsOverlay.draw();

        m_window.swapBuffers(); 
        m_window.pollEvents();
    }

    LOG_INFO("Main loop exited.");
}

} // namespace ball_sim