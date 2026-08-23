// Presenter.h
#ifndef BALL_SIM_PRESENTER_H
#define BALL_SIM_PRESENTER_H

#include <vector>
#include "core/objects/Ball.h"
#include "render/Shader.h"
#include "render/CircleRenderer.h"

namespace ball_sim {

inline constexpr const char* kVertexShaderSource = R"(
    #version 460 core
    layout (location = 0) in vec3 aPos;
    uniform vec2 uOffset;
    uniform float uRadius;
    void main() {
        // Scale unit circle by ball radius, then translate by position
        vec2 pos = (aPos.xy * uRadius) + uOffset;
        gl_Position = vec4(pos, aPos.z, 1.0);
    }
)";

inline constexpr const char* kFragmentShaderSource = R"(
    #version 460 core
    out vec4 FragColor;
    uniform vec4 uColor;
    
    void main() {
        FragColor = uColor;
    }
)";

class Presenter {
private:
    render::Shader m_shader;
    render::CircleRenderer m_circleRenderer;

public:
    Presenter(const std::vector<float>& circleVertices);
    ~Presenter() = default;

    void pres_step(const std::vector<core::Ball>& balls);
};

} // namespace ball_sim

#endif // BALL_SIM_PRESENTER_H