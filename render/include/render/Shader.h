#ifndef RENDER_SHADER_H
#define RENDER_SHADER_H

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace render {

class Shader {
public:
    Shader() = default;
    Shader(const char* vertexSource, const char* fragmentSource);
    ~Shader();

    // Prevent copying (GPU handle ownership safety)
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    // Enable move semantics (required for storing inside Presenter/containers)
    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    void use() const;
    
    // Uniform setters
    void setFloat(const char* name, float value) const;
    void setVec2(const char* name, const glm::vec2& value) const;
    void setVec4(const char* name, const glm::vec4& value) const;

private:
    GLuint compileShader(GLenum type, const char* source);
    GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader);

    GLuint m_programID{0};
};

} // namespace render

#endif // RENDER_SHADER_H