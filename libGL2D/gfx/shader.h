#ifndef _LIBGL2D_GFX_SHADER_H_
#define _LIBGL2D_GFX_SHADER_H_

#include <GL/gl.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "libGL2D/core/using.h"
#include "libGL2D/physics/math.h"

namespace libgl {

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

}  // namespace libgl

#endif  // _LIBGL2D_GFX_SHADER_H_