#include "render/CircleRenderer.h"
#include "core/utils/Logger.h"

namespace render {

CircleRenderer::CircleRenderer(const std::vector<float>& vertices) 
    : m_vertexCount(static_cast<GLsizei>(vertices.size() / 3)) {

    LOG_INFO("Creating CircleRenderer with {} vertices ({} triangles/segments)", m_vertexCount, m_vertexCount - 2);

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    LOG_TRACE("CircleRenderer GPU buffers initialized: VAO={}, VBO={}", m_vao, m_vbo);
}

CircleRenderer::~CircleRenderer() {
    LOG_INFO("Destroying CircleRenderer: VAO={}, VBO={}", m_vao, m_vbo);

    if (m_vbo != 0) glDeleteBuffers(1, &m_vbo);
    if (m_vao != 0) glDeleteVertexArrays(1, &m_vao);
}

void CircleRenderer::draw() const {
    if (m_vao == 0) {
        LOG_ERROR("Attempted to draw CircleRenderer with uninitialized VAO!");
        return;
    }

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, m_vertexCount);
    glBindVertexArray(0);
}

}