#include "shader.h"

#include <GL/gl.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "libGL2D/gfx/errors.h"

namespace libGL2D {

Shader::Shader(const std::string& filepath) : filepath_(filepath) {
	ShaderProgramSource source = ParseShader();
	id_ = CreateShader(source.vertex_source, source.fragment_source);
}

Shader::~Shader() {
	glDeleteProgram(id_);
}

void Shader::Bind() const {
	glUseProgram(id_);
}

void Shader::Unbind() const {
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value) {
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value) {
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2) {
	glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform2f(const std::string& name, float v0, float v1) {
	glUniform2f(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
	// glm::mat4 stores data in columns which is OpenGL standard so no transpose needed
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniform1iv(const std::string& name, int* arr, uint32_t size) {
	glUniform1iv(GetUniformLocation(name), size, arr);
}

void Shader::SetUniformBool(const std::string& name, bool v0) {
	glUniform1i(GetUniformLocation(name), v0);
}

GLint Shader::GetUniformLocation(const std::string& name) {
	Bind();
	if (uniform_loc_cache_.find(name) != uniform_loc_cache_.end()) {
		return uniform_loc_cache_[name];
	}
	GLint loc = glGetUniformLocation(id_, name.c_str());
	if (loc == -1) {
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	}
	uniform_loc_cache_[name] = loc;
	return loc;
}

ShaderProgramSource Shader::ParseShader() {
	std::ifstream stream(filepath_);
	std::string line;

	enum class ShaderType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::stringstream shaderstream[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
				// vertex shader
			} else if (line.find("fragment") != std::string::npos) {
				// fragment shader
				type = ShaderType::FRAGMENT;
			}
		} else {
			shaderstream[(int)type] << line << '\n';
		}
	}
	return {shaderstream[0].str(), shaderstream[1].str()};
}

GLuint Shader::CompileShader(uint32_t type, const std::string& source) {
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int res;
	glGetShaderiv(id, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE) {
		GLint length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(sizeof(char) * length);
		glGetShaderInfoLog(id, length, nullptr, message);
		std::cout << "Failed to compile: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		free(message);
		glDeleteShader(id);
		return 0;
	}

	return id;
}

/**
 * @return binding for shader
 */
GLuint Shader::CreateShader(const std::string& vertex_shader, const std::string& fragment_shader) {
	GLuint program = glCreateProgram();

	GLuint vertexs = CompileShader(GL_VERTEX_SHADER, vertex_shader);
	GLuint frags = CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

	glAttachShader(program, vertexs);
	glAttachShader(program, frags);

	glLinkProgram(program);
	glValidateProgram(program);
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		int length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(sizeof(char) * length);
		glGetProgramInfoLog(program, 512, nullptr, message);
		std::cout << "Failed to link shader: " << message << std::endl;
		free(message);
		glDeleteShader(program);
		return 0;
	}

	glDeleteShader(vertexs);
	glDeleteShader(frags);

	return program;
}

void ShaderManager::Load(const std::string& shader_name, const std::string& filepath) {
	shaders[shader_name] = std::make_shared<Shader>(filepath);
}

Sptr<Shader> ShaderManager::Get(const std::string& shader_name) {
	return shaders[shader_name];
}

bool ShaderManager::Contains(const std::string& shader_name) {
	return shaders.find(shader_name) != shaders.end();
}

Sptr<Shader> ShaderManager::operator[](const std::string& shader_name) {
	return Get(shader_name);
}

}  // namespace libGL2D
