#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

#include <tuple>
#include <utility>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

struct GLFWwindow;

namespace render {

class Window {
private:
    GLFWwindow* m_window{nullptr};

    int m_width{800};
    int m_height{800};
    float m_baseHeight{800.0f};
    bool m_isResized{false};

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
public:
    Window(int width, int height, const char* title);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool isValid() const;
    bool shouldClose() const;
    void pollEvents() const;
    void swapBuffers() const;
    GLFWwindow* getNativeWindow() const;

    void processInput();
    bool isKeyPressed(int key) const;
    bool isMouseButtonPressed(int button) const;    
    std::pair<double, double> getCursorPosition() const;
    std::pair<int, int> getDimensions() const;

    float getAspectRatio() const;
    glm::mat4 getProjectionMatrix() const;
    std::pair<glm::vec2, glm::vec2> getWorldBounds() const;
    glm::vec2 screenToWorld(double xpos, double ypos) const;
    bool isResized() const;
    bool consumeResizeFlag();
    // TODO: Fix the ordering of the fucntions above
};

}

#endif