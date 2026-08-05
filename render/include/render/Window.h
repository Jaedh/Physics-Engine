#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

struct GLFWwindow;

namespace render {

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool isValid() const { return m_window != nullptr; }
    bool shouldClose() const;
    void pollEvents() const;
    void swapBuffers() const;
    void processInput();

    GLFWwindow* getNativeWindow() const { return m_window; }

private:
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    GLFWwindow* m_window{nullptr};
};

} // namespace render

#endif // RENDER_WINDOW_H