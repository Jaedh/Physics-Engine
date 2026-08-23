#include "render/Window.h"
#include "render/Shader.h"
#include "render/CircleRenderer.h"

#include "World.h"
#include "Presenter.h"

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

} // namespace

int main() {
    // WINDOW SETUP
    render::Window window(kWindowWidth, kWindowHeight, "Ball Sim");
    if (!window.isValid()) return -1;

    // WORLD SIMULATION SETUP
    ball_sim::World world;

    // BALL SETUP
    std::vector<core::Ball> ball_array;
    core::Ball ball_1;

    core::Ball ball_2;
    ball_2.position = glm::vec2(0.25f, 0.25f);
    ball_2.color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

    ball_array.push_back(ball_1);
    ball_array.push_back(ball_2);
    // TODO: Make a function to add balls with random positions, velocities, and colors for testing

    // PRESENTER SETUP
    ball_sim::Presenter presenter(core::math::generateCircleVertices(0.0f, 0.0f, 1.0f, 64));

    // Main update loop 
    while (!window.shouldClose()) {
        // PROCESS INPUT
        window.processInput();

        // STEP WORLD SIMULATION
        world.step(ball_array);

        // STEP PRESENTER RENDERING
        presenter.pres_step(ball_array);

        // DISPLAY FRAME
        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}