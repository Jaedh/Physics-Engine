// Presenter.h
#ifndef BALL_SIM_PRESENTER_H
#define BALL_SIM_PRESENTER_H

#include <vector>
#include <glm/mat4x4.hpp>

#include "core/objects/Ball.h"
#include "render/Shader.h"
#include "render/CircleRenderer.h"

namespace ball_sim {

inline constexpr const char* kVertexShaderSource = R"(
    #version 460 core
    layout (location = 0) in vec3 aPos;

    out vec2 vUV;
    
    uniform vec2 uOffset;
    uniform float uRadius;
    uniform mat4 uProjection;

    void main() {
        vUV = aPos.xy;
        vec3 scaledPos = vec3(aPos.x * uRadius + uOffset.x, aPos.y * uRadius + uOffset.y, aPos.z);
        gl_Position = uProjection * vec4(scaledPos, 1.0);    
    }
)";

inline constexpr const char* kFragmentShaderSource = R"(
    #version 460 core
    in vec2 vUV;
    out vec4 FragColor;

    uniform vec4 uColor;
    uniform vec4 uBorderColor;
    uniform float uBorderThickness;

void main() {
        float dist = length(vUV);

        float delta = fwidth(dist);
        float alpha = 1.0 - smoothstep(1.0 - delta, 1.0, dist);

        if (alpha <= 0.0) discard;

        float borderEdge = 1.0 - uBorderThickness;
        float borderFactor = smoothstep(borderEdge - delta, borderEdge, dist);

        vec3 finalRGB = mix(uColor.rgb, uBorderColor.rgb, borderFactor);

        FragColor = vec4(finalRGB, uColor.a * alpha);
    }
)";

class Presenter {
private:
    render::Shader m_shader;
    render::CircleRenderer m_circleRenderer;

public:
    Presenter(const std::vector<float>& circleVertices);
    ~Presenter() = default;

    void pres_step(const std::vector<core::Ball>& balls, float aspectRatio);
};

}

#endif 