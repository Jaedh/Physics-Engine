#ifndef RENDER_CIRCLE_RENDERER_H
#define RENDER_CIRCLE_RENDERER_H

#include <glad/glad.h>
#include <vector>

namespace render {

class CircleRenderer {
public:
    CircleRenderer(const std::vector<float>& vertices);
    ~CircleRenderer();

    CircleRenderer(const CircleRenderer&) = delete;
    CircleRenderer& operator=(const CircleRenderer&) = delete;

    void draw() const;

private:
    GLuint m_vao{0};
    GLuint m_vbo{0};
    GLsizei m_vertexCount{0};
};

} // namespace render

#endif // RENDER_CIRCLE_RENDERER_H