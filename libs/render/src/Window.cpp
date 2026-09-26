#include "render/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "core/utils/Logger.h"

namespace render {

Window::Window(int width, int height, const char* title)
    : m_width(width), m_height(height), m_baseHeight(static_cast<float>(height)) {
    
    LOG_INFO("Initializing GLFW window '{}' ({}x{})...", title, width, height);

    if (!glfwInit()) {
        LOG_CRITICAL("Failed to initialize GLFW library!");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_window) {
        LOG_CRITICAL("Failed to create GLFW window context!");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        LOG_CRITICAL("Failed to initialize GLAD OpenGL loader!");
        glfwDestroyWindow(m_window);
        m_window = nullptr;
        glfwTerminate();
        return;
    }

    LOG_INFO("OpenGL Context Created Successfully.");
    LOG_INFO("Vendor:   {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    LOG_INFO("Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    LOG_INFO("Version:  {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

Window::~Window() {
    LOG_INFO("Destroying GLFW Window subsystem.");
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

bool Window::isValid() const { 
    return m_window != nullptr; 
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void Window::pollEvents() const {
    glfwPollEvents();
}

void Window::swapBuffers() const {
    glfwSwapBuffers(m_window);
}

GLFWwindow* Window::getNativeWindow() const {
    return m_window;
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    if (width == 0 || height == 0) {
        LOG_WARN("Framebuffer resized to zero dimensions (minimized context).");
        return;
    }
    
    glViewport(0, 0, width, height);
    
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (self) {
        self->m_width = width;
        self->m_height = height;
        self->m_isResized = true;
        LOG_DEBUG("Framebuffer resized to {}x{}", width, height);
    }
}

void Window::processInput() {
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        LOG_INFO("Escape key pressed. Flagging window to close.");
        glfwSetWindowShouldClose(m_window, true);
    }
}

bool Window::isKeyPressed(int key) const {
    return glfwGetKey(m_window, key) == GLFW_PRESS;
}

bool Window::isMouseButtonPressed(int button) const {
    return glfwGetMouseButton(m_window, button) == GLFW_PRESS;
}

std::pair<double, double> Window::getCursorPosition() const {
    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);
    return {xpos, ypos};
}

std::pair<int, int> Window::getDimensions() const {
    return {m_width, m_height};
}

float Window::getAspectRatio() const {
    if (m_height == 0) return 1.0f;
    return static_cast<float>(m_width) / static_cast<float>(m_height);
}

glm::mat4 Window::getProjectionMatrix() const {
    if (m_height == 0) return glm::mat4(1.0f);

    float halfWidth = static_cast<float>(m_width) / m_baseHeight;
    float halfHeight = static_cast<float>(m_height) / m_baseHeight;

    return glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1.0f, 1.0f);
}

std::pair<glm::vec2, glm::vec2> Window::getWorldBounds() const {
    if (m_height == 0) return { glm::vec2(-1.0f), glm::vec2(1.0f) };

    float halfWidth = static_cast<float>(m_width) / m_baseHeight;
    float halfHeight = static_cast<float>(m_height) / m_baseHeight;

    return { glm::vec2(-halfWidth, -halfHeight), glm::vec2(halfWidth, halfHeight) };
}

glm::vec2 Window::screenToWorld(double xpos, double ypos) const {
    if (m_width == 0 || m_height == 0) return glm::vec2(0.0f);

    float halfWidth = static_cast<float>(m_width) / m_baseHeight;
    float halfHeight = static_cast<float>(m_height) / m_baseHeight;

    float worldX = ((static_cast<float>(xpos) / m_width) * 2.0f - 1.0f) * halfWidth;
    float worldY = (1.0f - (static_cast<float>(ypos) / m_height) * 2.0f) * halfHeight;

    return glm::vec2(worldX, worldY);
}

bool Window::isResized() const { 
    return m_isResized; 
}

bool Window::consumeResizeFlag() {
    bool temp = m_isResized;
    m_isResized = false;
    return temp;
}

} // namespace render