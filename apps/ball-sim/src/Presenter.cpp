// Presenter.cpp
#include "Presenter.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace ball_sim {

Presenter::Presenter(const std::vector<float>& circleVertices)
    : m_shader(kVertexShaderSource, kFragmentShaderSource),
      m_circleRenderer(circleVertices) {}

void Presenter::pres_step(const std::vector<core::Ball>& balls, float aspectRatio) {
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);          

    if (aspectRatio == 0) return;

    glm::mat4 projection = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

    m_shader.use();
    m_shader.setMat4("uProjection", projection);

    for (const auto& ball : balls) {
        m_shader.setVec2("uOffset", ball.position);
        m_shader.setFloat("uRadius", ball.radius);
        m_shader.setVec4("uColor", ball.color);
        m_circleRenderer.draw();
    }
}

} 