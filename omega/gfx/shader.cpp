#include "shader.hpp"

#include <GL/gl.h>

#include <fstream>
#include <iostream>
#include <sstream>

namespace omega::gfx {

Shader::Shader(const std::string &filepath) {
    ShaderProgramSource source = parse_shader(filepath);
    id = create_shader(source.vertex_source, source.fragment_source);
}

Shader::Shader(const std::string &vertex_source, const std::string &fragment_source) {
    id = create_shader(vertex_source, fragment_source);
}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::bind() const {
    glUseProgram(id);
}

void Shader::set_uniform_1i(const std::string &name, int value) {
    glUniform1i(get_uniform_location(name), value);
}

void Shader::set_uniform_1f(const std::string &name, float value) {
    glUniform1f(get_uniform_location(name), value);
}

void Shader::set_uniform_4f(const std::string &name, float v0, float v1, float v2, float v3) {
    glUniform4f(get_uniform_location(name), v0, v1, v2, v3);
}

void Shader::set_uniform_3f(const std::string &name, float v0, float v1, float v2) {
    glUniform3f(get_uniform_location(name), v0, v1, v2);
}

void Shader::set_uniform_2f(const std::string &name, float v0, float v1) {
    glUniform2f(get_uniform_location(name), v0, v1);
}

void Shader::set_uniform_mat4f(const std::string &name, const glm::mat4 &matrix) {
    // glm::mat4 stores data in columns which is OpenGL standard so no transpose needed
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::set_uniform_1iv(const std::string &name, int *arr, uint32_t size) {
    glUniform1iv(get_uniform_location(name), size, arr);
}

void Shader::set_uniform_bool(const std::string &name, bool v0) {
    glUniform1i(get_uniform_location(name), v0);
}

int Shader::get_uniform_location(const std::string &name) {
    bind();
    if (uniform_loc_cache.find(name) != uniform_loc_cache.end()) {
        return uniform_loc_cache[name];
    }
    GLint loc = glGetUniformLocation(id, name.c_str());
    if (loc == -1) {
        util::error("Warning: uniform '", name, "' doesn't exist!");
    }
    uniform_loc_cache[name] = loc;
    return loc;
}

Shader::ShaderProgramSource Shader::parse_shader(const std::string &filepath) {
    std::ifstream stream(filepath);
    std::string line;

    enum class ShaderType {
        none = -1,
        vertex = 0,
        fragment = 1
    };

    std::stringstream shaderstream[2];
    ShaderType type = ShaderType::none;
    while (std::getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::vertex;
                // vertex shader
            } else if (line.find("fragment") != std::string::npos) {
                // fragment shader
                type = ShaderType::fragment;
            }
        } else {
            shaderstream[(int)type] << line << '\n';
        }
    }
    return {shaderstream[0].str(), shaderstream[1].str()};
}

uint32_t Shader::compile_shader(uint32_t type, const std::string &source) {
    GLuint id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int res;
    glGetShaderiv(id, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE) {
        GLint length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)malloc(sizeof(char) * length);
        glGetShaderInfoLog(id, length, nullptr, message);
        util::error("Failed to compile: ", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), " shader!");
        util::error(message);
        free(message);
        glDeleteShader(id);
        return 0;
    }

    return id;
}

/**
 * @return binding for shader
 */
uint32_t Shader::create_shader(const std::string &vertex_shader, const std::string &fragment_shader) {
    GLuint program = glCreateProgram();

    GLuint vertexs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    GLuint frags = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

    glAttachShader(program, vertexs);
    glAttachShader(program, frags);

    glLinkProgram(program);
    glValidateProgram(program);
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        int length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)malloc(sizeof(char) * length);
        glGetProgramInfoLog(program, 512, nullptr, message);
        util::error("Failed to link shader: ", message);
        free(message);
        glDeleteShader(program);
        return 0;
    }

    glDeleteShader(vertexs);
    glDeleteShader(frags);

    return program;
}

} // namespace omega::gfx
