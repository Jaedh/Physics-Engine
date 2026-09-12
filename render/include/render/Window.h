#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

#include <tuple>

struct GLFWwindow;

namespace render {

class Window {
private:
    GLFWwindow* m_window{nullptr};

    int m_width{800};
    int m_height{800};

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
};

}

#endif