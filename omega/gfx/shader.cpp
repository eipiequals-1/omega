#include "shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include "omega/gfx/gl.hpp"

namespace omega::gfx {

Shader::Shader(const std::string &filepath) {
    ShaderProgramSource source = parse_shader(filepath);
    id = create_shader(
        source.vertex_source, source.fragment_source, source.geometry_source);
}

Shader::Shader(const std::string &vertex_source,
               const std::string &fragment_source) {
    id = create_shader(vertex_source, fragment_source, "");
}

Shader::Shader(const std::string &vertex_source,
               const std::string &fragment_source,
               const std::string &geometry_source) {
    id = create_shader(vertex_source, fragment_source, geometry_source);
}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::bind() const {
    glUseProgram(id);
}

void Shader::unbind() {
    glUseProgram(0);
}

void Shader::set_uniform_1i(const std::string &name, i32 value) {
    glUniform1i(get_uniform_location(name), value);
}

void Shader::set_uniform_1f(const std::string &name, float value) {
    glUniform1f(get_uniform_location(name), value);
}

void Shader::set_uniform_4f(const std::string &name,
                            float v0,
                            float v1,
                            float v2,
                            float v3) {
    glUniform4f(get_uniform_location(name), v0, v1, v2, v3);
}

void Shader::set_uniform_4f(const std::string &name, const math::vec4 &v) {
    set_uniform_4f(name, v.x, v.y, v.z, v.w);
}

void Shader::set_uniform_3f(const std::string &name,
                            float v0,
                            float v1,
                            float v2) {
    glUniform3f(get_uniform_location(name), v0, v1, v2);
}

void Shader::set_uniform_3f(const std::string &name, const math::vec3 &v) {
    set_uniform_3f(name, v.x, v.y, v.z);
}

void Shader::set_uniform_2f(const std::string &name, float v0, float v1) {
    glUniform2f(get_uniform_location(name), v0, v1);
}

void Shader::set_uniform_2f(const std::string &name, const math::vec2 &v) {
    set_uniform_2f(name, v.x, v.y);
}

void Shader::set_uniform_mat4f(const std::string &name,
                               const math::mat4 &matrix) {
    // math::mat4 stores data in columns which is OpenGL standard so no
    // transpose needed
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::set_uniform_1iv(const std::string &name, i32 *arr, u32 size) {
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
        util::warn("Warning: uniform '{}' doesn't exist", name);
    }
    uniform_loc_cache[name] = loc;
    return loc;
}

Shader::ShaderProgramSource Shader::parse_shader(const std::string &filepath) {
    std::ifstream stream(filepath);
    std::string line;

    enum class ShaderType { none = -1, vertex = 0, fragment = 1, geometry = 2 };

    std::stringstream shaderstream[3];
    ShaderType type = ShaderType::none;
    while (std::getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::vertex;
                // vertex shader
            } else if (line.find("fragment") != std::string::npos) {
                // fragment shader
                type = ShaderType::fragment;
            } else if (line.find("geometry") != std::string::npos) {
                // gemoetry shader
                type = ShaderType::geometry;
            }
        } else {
            shaderstream[(int)type] << line << '\n';
        }
    }
    return {
        shaderstream[0].str(), shaderstream[1].str(), shaderstream[2].str()};
}

u32 Shader::compile_shader(u32 type, const std::string &source) {
    GLuint id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    i32 res;
    glGetShaderiv(id, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE) {
        GLint length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)malloc(sizeof(char) * length);
        glGetShaderInfoLog(id, length, nullptr, message);
        util::err("Failed to compile: {} shader!",
                  (type == GL_VERTEX_SHADER       ? "vertex"
                   : (type == GL_FRAGMENT_SHADER) ? "fragment"
                                                  : "geometry"));
        util::err(message);
        free(message);
        glDeleteShader(id);
        return 0;
    }

    return id;
}

/**
 * @return binding for shader
 */
u32 Shader::create_shader(const std::string &vertex_shader,
                          const std::string &fragment_shader,
                          const std::string &geometry_shader) {
    GLuint program = glCreateProgram();

    GLuint vertexs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    GLuint frags = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);
#ifndef EMSCRIPTEN
    GLuint geometrys = 0;
    if (geometry_shader != "") {
        geometrys = compile_shader(GL_GEOMETRY_SHADER, geometry_shader);
    }
#endif

    glAttachShader(program, vertexs);
    glAttachShader(program, frags);

#ifndef EMSCRIPTEN
    if (geometrys != 0) {
        glAttachShader(program, geometrys);
    }
#endif

    glLinkProgram(program);
    glValidateProgram(program);
    i32 success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        i32 length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)malloc(sizeof(char) * length);
        glGetProgramInfoLog(program, 512, nullptr, message);
        util::err("Failed to link shader: {}", message);
        free(message);
        glDeleteShader(program);
        return 0;
    }

    glDeleteShader(vertexs);
    glDeleteShader(frags);
#ifndef EMSCRIPTEN
    if (geometrys != 0) {
        glDeleteShader(geometrys);
    }
#endif
    return program;
}

} // namespace omega::gfx
