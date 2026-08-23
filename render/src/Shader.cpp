#include "render/Shader.h"
#include <iostream>
#include <utility>

namespace render {

Shader::Shader(const char* vertexSource, const char* fragmentSource) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
    m_programID = linkProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    if (m_programID != 0) {
        glDeleteProgram(m_programID);
    }
}

// Move constructor
Shader::Shader(Shader&& other) noexcept 
    : m_programID(std::exchange(other.m_programID, 0)) {}

// Move assignment operator
Shader& Shader::operator=(Shader&& other) noexcept {
    if (this != &other) {
        if (m_programID != 0) {
            glDeleteProgram(m_programID);
        }
        m_programID = std::exchange(other.m_programID, 0);
    }
    return *this;
}

void Shader::use() const {
    if (m_programID != 0) {
        glUseProgram(m_programID);
    }
}

void Shader::setFloat(const char* name, float value) const {
    GLint loc = glGetUniformLocation(m_programID, name);
    if (loc != -1) {
        glUniform1f(loc, value);
    }
}

void Shader::setVec2(const char* name, const glm::vec2& value) const {
    GLint loc = glGetUniformLocation(m_programID, name);
    if (loc != -1) {
        glUniform2f(loc, value.x, value.y);
    }
}

void Shader::setVec4(const char* name, const glm::vec4& value) const {
    GLint loc = glGetUniformLocation(m_programID, name);
    if (loc != -1) {
        glUniform4f(loc, value.x, value.y, value.z, value.w);
    }
}

GLuint Shader::compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        std::cerr << "Shader compile error:\n" << log << std::endl;
    }
    return shader;
}

GLuint Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(program, sizeof(log), nullptr, log);
        std::cerr << "Shader link error:\n" << log << std::endl;
    }
    return program;
}

} // namespace render