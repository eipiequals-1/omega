#ifndef OMEGA_GFX_SHADER_HPP
#define OMEGA_GFX_SHADER_HPP

#include <cstdint>
#include <string>
#include <unordered_map>

#include "omega/util/log.hpp"
#include "omega/util/math.hpp"
#include "omega/util/std.hpp"

namespace omega::gfx {

using namespace omega::util;

/**
 * OpenGL shader abstraction that stores a vertex and fragment shader
 */
class Shader {
  public:
    explicit Shader(const std::string &filepath);
    Shader(const std::string &vertex_source,
           const std::string &fragment_source);
    ~Shader();

    /**
     * Binds the shader in the OpenGL state machine
     */
    void bind() const;

    /**
     * Unbinds the shader in the OpenGL state machine
     */
    static void unbind();

    // set uniforms
    void set_uniform_4f(const std::string &name,
                        float v0, float v1, float v2, float v3);
    void set_uniform_3f(const std::string &name, float v0, float v1, float v2);
    void set_uniform_2f(const std::string &name, float v0, float v1);
    void set_uniform_1f(const std::string &name, float value);
    void set_uniform_1i(const std::string &name, int value);
    void set_uniform_mat4f(const std::string &name, const glm::mat4 &matrix);
    void set_uniform_1iv(const std::string &name, int *arr, uint32_t size);

    void set_uniform_bool(const std::string &name, bool v0);
    uint32_t get_id() const { return id; }

  private:
    /**
     * Stores the vertex and fragment shaders source
     */
    struct ShaderProgramSource {
        std::string vertex_source;
        std::string fragment_source;
    };

    /**
     * Parses the shader from the given source file
     * @param path the shader
     * @return the struct containing the vertex and fragment source code
     */
    Shader::ShaderProgramSource parse_shader(const std::string &filepath);

    /**
     * Returns the location of the shader
     * @param name of the uniform
     * @return the GL location of the uniform
     */
    int get_uniform_location(const std::string &name);

    /**
     * Compiles the shader based off the type of the shader
     * @param type the GL type of shader i.e. GL_VERTEX_SHADER
     * @param source the code
     * @return the GL shader object
     */
    uint32_t compile_shader(uint32_t type, const std::string &source);

    /**
     * Compiles both shaders and links them to create THE GL shader object
     * @param vertex_shader the vertex source code
     * @param fragment_shader the fragment source code
     * @return the GL shader object
     */
    uint32_t create_shader(const std::string &vertex_shader,
                           const std::string &fragment_shader);

    uint32_t id;
    std::unordered_map<std::string, int> uniform_loc_cache;
};

template <typename K>
class ShaderManager {
  public:
    ShaderManager() = default;
    ~ShaderManager() = default;

    sptr<Shader> load(const K &id, const std::string &filepath) {
        if (!contains(id)) {
            shaders[id] = create_sptr<Shader>(filepath);
        }
        return shaders[id];
    }

    sptr<Shader> get(const K &id) {
        if (contains(id)) {
            return shaders[id];
        }
        return nullptr;
    }

    bool contains(const K &id) {
        return shaders.find(id) != shaders.end();
    }

    sptr<Shader> operator[](const K &id) {
        return get(id);
    }

  private:
    std::unordered_map<K, sptr<Shader>> shaders;
};

} // namespace omega::gfx

#endif // OMEGA_GFX_SHADER_HPP
