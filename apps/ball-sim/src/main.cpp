#include "render/Window.h"
#include "render/Shader.h"
#include "render/CircleRenderer.h"

#include "World.h"
#include "core/math/CircleGeometry.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


// #include "App.h"

// Add a json list list to outline all the app prameters and settings  

// int main() {
//     ball_sim::App app(800, 600, "Ball Sim");
//     app.run();
//     return 0;
// }


namespace {

constexpr int kWindowWidth = 800;
constexpr int kWindowHeight = 800;

const char* kVertexShaderSource = R"(
    #version 460 core
    layout (location = 0) in vec3 aPos;
    uniform vec2 uOffset;
    void main() {
        gl_Position = vec4(aPos.x + uOffset.x, aPos.y + uOffset.y, aPos.z, 1.0);
    }
)";

const char* kFragmentShaderSource = R"(
    #version 460 core
    out vec4 FragColor;
    uniform vec4 uColor; // Recieves color from Ball.h
    
    void main() {
        FragColor = uColor;
    }
)";

} // namespace

int main() {
    // Initialize windowing system
    render::Window window(kWindowWidth, kWindowHeight, "Ball Sim");
    if (!window.isValid()) return -1;

    // Compile shader pipeline and initialize the ImGui debug overlay wrapper
    render::Shader shader(kVertexShaderSource, kFragmentShaderSource);

    // Ball
    ball_sim::World world;
    world.addBall(core::Ball{});

    core::Ball ball;
    ball.position = glm::vec2(0.25f, 0.25f);
    world.addBall(ball);

    // Compute circle geometry points and upload vertex data to GPU memory (VBO/VAO)
    std::vector<float> circleData = core::math::generateCircleVertices(0.0f, 0.0f, 0.2f, 64);
    render::CircleRenderer circleRenderer(circleData);

    // Setup high-precision frame timing for time-delta updates
    float lastFrameTime = static_cast<float>(glfwGetTime());

    // Main update loop 
    while (!window.shouldClose()) {
        // Calculate frame delta time in seconds
        float currentFrameTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // Process keyboard and window events
        window.processInput();

        // Step the core physics simulation engine
        world.step(deltaTime);

        // Clear frame buffer and enable alpha blending for transparent rendering
        glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);          

        // Render each ball using the shader uniforms and circle geometry
        shader.use();
        for (const auto& ball : world.getBalls()) {
            shader.setVec2("uOffset", ball.position);
            shader.setVec4("uColor", ball.color);
            circleRenderer.draw();
        }

        // Display updated frame and handle window events
        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}