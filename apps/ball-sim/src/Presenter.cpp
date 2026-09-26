#include "Presenter.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "core/utils/Logger.h"

namespace ball_sim {

Presenter::Presenter(const std::vector<float>& circleVertices)
    : m_shader(kVertexShaderSource, kFragmentShaderSource),
      m_circleRenderer(circleVertices) {
    LOG_INFO("Presenter initialized with {} vertex floats.", circleVertices.size());
}

void Presenter::presenter_step(const std::vector<core::Ball>& balls, const glm::mat4& projection) {
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);          

    if (projection == glm::mat4(0.0f)) {
        LOG_WARN("Presenter received a zero projection matrix. Skipping frame render step.");
        return;
    }

    // LOG_TRACE("Presenter rendering frame for {} ball entities.", balls.size());

    m_shader.use();
    m_shader.setMat4("uProjection", projection);

    for (const auto& ball : balls) {
        m_shader.setVec2("uOffset", ball.position);
        m_shader.setFloat("uRadius", ball.radius);
        m_shader.setVec4("uColor", ball.color);
        m_circleRenderer.draw();
    }
}

} // namespace ball_sim