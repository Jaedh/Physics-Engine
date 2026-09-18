// Presenter.cpp
#include "Presenter.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace ball_sim {

Presenter::Presenter(const std::vector<float>& circleVertices)
    : m_shader(kVertexShaderSource, kFragmentShaderSource),
      m_circleRenderer(circleVertices) {}

void Presenter::presenter_step(const std::vector<core::Ball>& balls, const glm::mat4& projection) {
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);          

    if (projection == glm::mat4(0.0f)) return;

    m_shader.use();
    m_shader.setMat4("uProjection", projection);

    // TODO: Add border rendering support in the future
    // m_shader.setVec4("uBorderColor", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    // m_shader.setFloat("uBorderThickness", 0.08f);

    for (const auto& ball : balls) {
        m_shader.setVec2("uOffset", ball.position);
        m_shader.setFloat("uRadius", ball.radius);
        m_shader.setVec4("uColor", ball.color);
        m_circleRenderer.draw();
    }
}

} 