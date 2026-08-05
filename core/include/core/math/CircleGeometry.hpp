#ifndef CORE_MATH_CIRCLE_GEOMETRY_HPP
#define CORE_MATH_CIRCLE_GEOMETRY_HPP

#include <vector>
#include <cmath>

namespace core::math {

inline std::vector<float> generateCircleVertices(float centerX, float centerY, float radius, int segments) {
    std::vector<float> vertices;
    vertices.reserve((segments + 2) * 3);
    
    // Center vertex
    vertices.push_back(centerX);
    vertices.push_back(centerY);
    vertices.push_back(0.0f);

    constexpr float kTwoPi = 6.28318530718f;
    for (int i = 0; i <= segments; ++i) {
        float angle = i * (kTwoPi / segments);
        vertices.push_back(centerX + radius * std::cos(angle));
        vertices.push_back(centerY + radius * std::sin(angle));
        vertices.push_back(0.0f);
    }

    return vertices;
}

} // namespace core::math

#endif // CORE_MATH_CIRCLE_GEOMETRY_HPP