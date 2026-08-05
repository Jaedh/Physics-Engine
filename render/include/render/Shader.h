#ifndef RENDER_SHADER_H
#define RENDER_SHADER_H

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace render {

class Shader {
public:
    Shader(const char* vertexSource, const char* fragmentSource);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void use() const;
    void setVec2(const char* name, const glm::vec2& value) const;
    // void setVec3(const char* name, const glm::vec3& value) const;
    void setVec4(const char* name, const glm::vec4& valuew) const;
private:
    GLuint compileShader(GLenum type, const char* source);
    GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader);

    GLuint m_programID{0};
};

} // namespace render

#endif // RENDER_SHADER_H