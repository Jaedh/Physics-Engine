#include "render/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

namespace render {

Window::Window(int width, int height, const char* title)
    : m_width(width), m_height(height), m_baseHeight(static_cast<float>(height)) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD\n";
        glfwDestroyWindow(m_window);
        m_window = nullptr;
        glfwTerminate();
        return;
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}

Window::~Window() {
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
    if (width == 0 || height == 0) return;
    
    glViewport(0, 0, width, height);
    
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (self) {
        self->m_width = width;
        self->m_height = height;
        self->m_isResized = true;
    }
}

void Window::processInput() {
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
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

}