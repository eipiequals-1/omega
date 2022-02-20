#ifndef _LIBGL2D_GFX_SHADER_H_
#define _LIBGL2D_GFX_SHADER_H_

#include <GL/gl.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "libGL2D/core/using.h"
#include "libGL2D/physics/math.h"

namespace libGL2D {

struct ShaderProgramSource {
	std::string vertex_source;
	std::string fragment_source;
};

class Shader {
   public:
	explicit Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// set uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform2f(const std::string& name, float v0, float v1);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void SetUniform1iv(const std::string& name, int* arr, uint32_t size);

	void SetUniformBool(const std::string& name, bool v0);
	GLuint GetID() const { return id_; }

   private:
	ShaderProgramSource ParseShader();

	GLint GetUniformLocation(const std::string& name);
	GLuint CompileShader(uint32_t type, const std::string& source);
	GLuint CreateShader(const std::string& vertex_shader, const std::string& fragment_shader);

	GLuint id_;
	std::string filepath_;
	std::unordered_map<std::string, int> uniform_loc_cache_;
};

class ShaderManager {
   public:
	void Load(const std::string& shader_name, const std::string& filepath);
	Sptr<Shader> Get(const std::string& shader_name);
	bool Contains(const std::string& shader_name);

	Sptr<Shader> operator[](const std::string& shader_name);

   private:
	std::unordered_map<std::string, Sptr<Shader>> shaders;
};

}  // namespace libGL2D

#endif  // _LIBGL2D_GFX_SHADER_H_