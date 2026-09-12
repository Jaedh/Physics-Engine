#include "render/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace render {

Window::Window(int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return;
    }

    m_width = width;
    m_height = height;

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
    glViewport(0, 0, width, height);
    
    // Retrieve class instance and update stored dimensions
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (self) {
        self->m_width = width;
        self->m_height = height;
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

}