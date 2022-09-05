#ifndef OMEGA_GFX_SHADER_H
#define OMEGA_GFX_SHADER_H

#include <GL/gl.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "omega/util/util.h"

namespace omega {

/**
 * Stores the vertex and fragment shaders source
 */
struct ShaderProgramSource {
	std::string vertex_source;
	std::string fragment_source;
};

/**
 * OpenGL shader abstraction that stores a vertex and fragment shader
 */
class Shader {
   public:
	explicit Shader(const std::string& filepath);
	Shader(const std::string& vertex_source, const std::string& fragment_source);
	~Shader();

	/**
	 * Binds the shader in the OpenGL state machine
	 */
	void Bind() const;

	/**
	 * Unbinds the shader in the OpenGL state machine
	 */
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
	/**
	 * Parses the shader from the given source file
	 * @param path the shader
	 * @return the struct containing the vertex and fragment source code
	 */
	ShaderProgramSource ParseShader(const std::string& filepath);

	/**
	 * Returns the location of the shader
	 * @param name of the uniform
	 * @return the GL location of the uniform
	 */
	GLint GetUniformLocation(const std::string& name);

	/**
	 * Compiles the shader based off the type of the shader
	 * @param type the GL type of shader i.e. GL_VERTEX_SHADER
	 * @param source the code
	 * @return the GL shader object
	 */
	GLuint CompileShader(uint32_t type, const std::string& source);

	/**
	 * Compiles both shaders and links them to create THE GL shader object
	 * @param vertex_shader the vertex source code
	 * @param fragment_shader the fragment source code
	 * @return the GL shader object
	 */
	GLuint CreateShader(const std::string& vertex_shader, const std::string& fragment_shader);

	GLuint id_;
	std::unordered_map<std::string, int> uniform_loc_cache_;
};

template <typename K>
class ShaderManager {
   public:
	ShaderManager() = default;
	~ShaderManager() = default;

	sptr<Shader> Load(const K& id, const std::string& filepath) {
		if (!Contains(id)) {
			shaders_[id] = create_sptr<Shader>(filepath);
		}
		return shaders_[id];
	}

	sptr<Shader> Get(const K& id) {
		if (Contains(id)) {
			return shaders_[id];
		}
		return nullptr;
	}

	bool Contains(const K& id) {
		return shaders_.find(id) != shaders_.end();
	}

	sptr<Shader> operator[](const K& id) {
		return Get(id);
	}

   private:
	std::unordered_map<K, sptr<Shader>> shaders_;
};

}  // namespace omega

#endif  // OMEGA_GFX_SHADER_H