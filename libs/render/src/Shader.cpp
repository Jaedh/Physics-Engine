#include "render/Shader.h"

#include <utility>
#include <glm/gtc/type_ptr.hpp>

#include "core/utils/Logger.h"

namespace render {

Shader::Shader(const char* vertexSource, const char* fragmentSource) {
    LOG_INFO("Compiling and linking shader program...");
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
    m_programID = linkProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    if (m_programID != 0) {
        LOG_INFO("Shader program compiled and linked successfully. Program ID: {}", m_programID);
    } else {
        LOG_ERROR("Failed to construct valid shader program handle.");
    }
}

Shader::~Shader() {
    if (m_programID != 0) {
        LOG_INFO("Deleting GPU shader program ID: {}", m_programID);
        glDeleteProgram(m_programID);
    }
}

// Move constructor
Shader::Shader(Shader&& other) noexcept 
    : m_programID(std::exchange(other.m_programID, 0)) {
    LOG_TRACE("Shader program move constructed (ID: {})", m_programID);
}

// Move assignment operator
Shader& Shader::operator=(Shader&& other) noexcept {
    if (this != &other) {
        if (m_programID != 0) {
            LOG_INFO("Deleting overridden GPU shader program ID: {}", m_programID);
            glDeleteProgram(m_programID);
        }
        m_programID = std::exchange(other.m_programID, 0);
        LOG_TRACE("Shader program move assigned (ID: {})", m_programID);
    }
    return *this;
}

void Shader::use() const {
    if (m_programID != 0) {
        glUseProgram(m_programID);
    } else {
        LOG_WARN("Attempted to use uninitialized shader program.");
    }
}

void Shader::setFloat(const char* name, float value) const {
    GLint loc = glGetUniformLocation(m_programID, name);
    if (loc != -1) {
        glUniform1f(loc, value);
    } else {
        LOG_TRACE("Uniform '{}' not found in shader ID {}", name, m_programID);
    }
}

void Shader::setVec2(const char* name, const glm::vec2& value) const {
    GLint loc = glGetUniformLocation(m_programID, name);
    if (loc != -1) {
        glUniform2f(loc, value.x, value.y);
    } else {
        LOG_TRACE("Uniform '{}' not found in shader ID {}", name, m_programID);
    }
}

void Shader::setVec4(const char* name, const glm::vec4& value) const {
    GLint loc = glGetUniformLocation(m_programID, name);
    if (loc != -1) {
        glUniform4f(loc, value.x, value.y, value.z, value.w);
    } else {
        LOG_TRACE("Uniform '{}' not found in shader ID {}", name, m_programID);
    }
}

void Shader::setMat4(const char* name, const glm::mat4& value) const {
    GLint loc = glGetUniformLocation(m_programID, name);
    if (loc != -1) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    } else {
        LOG_TRACE("Uniform '{}' not found in shader ID {}", name, m_programID);
    }
}

GLuint Shader::compileShader(GLenum type, const char* source) {
    const char* shaderTypeName = (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment";
    LOG_TRACE("Compiling {} Shader...", shaderTypeName);

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        LOG_ERROR("{} Shader Compilation Error:\n{}", shaderTypeName, log);
    }
    return shader;
}

GLuint Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
    LOG_TRACE("Linking Shader Program...");
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(program, sizeof(log), nullptr, log);
        LOG_ERROR("Shader Program Link Error:\n{}", log);
    }
    return program;
}

} // namespace render