#ifndef OMEGA_GFX_SHADER_HPP
#define OMEGA_GFX_SHADER_HPP

#include <string>
#include <unordered_map>

#include "omega/math/math.hpp"
#include "omega/util/log.hpp"
#include "omega/util/std.hpp"
#include "omega/util/types.hpp"

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
    Shader(const std::string &vertex_source,
           const std::string &fragment_source,
           const std::string &geometry_source);

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
                        f32 v0,
                        f32 v1,
                        f32 v2,
                        f32 v3);
    void set_uniform_4f(const std::string &name, const math::vec4 &v);

    void set_uniform_3f(const std::string &name, f32 v0, f32 v1, f32 v2);
    void set_uniform_3f(const std::string &name, const math::vec3 &v);

    void set_uniform_2f(const std::string &name, f32 v0, f32 v1);
    void set_uniform_2f(const std::string &name, const math::vec2 &v);

    void set_uniform_1f(const std::string &name, f32 value);
    void set_uniform_1i(const std::string &name, i32 value);
    void set_uniform_mat4f(const std::string &name, const math::mat4 &matrix);
    void set_uniform_1iv(const std::string &name, i32 *arr, u32 size);

    void set_uniform_bool(const std::string &name, bool v0);
    u32 get_id() const {
        return id;
    }

  private:
    /**
     * Stores the vertex and fragment shaders source
     */
    struct ShaderProgramSource {
        std::string vertex_source;
        std::string fragment_source;
        std::string geometry_source;
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
    i32 get_uniform_location(const std::string &name);

    /**
     * Compiles the shader based off the type of the shader
     * @param type the GL type of shader i.e. GL_VERTEX_SHADER
     * @param source the code
     * @return the GL shader object
     */
    u32 compile_shader(u32 type, const std::string &source);

    /**
     * Compiles both shaders and links them to create THE GL shader object
     * @param vertex_shader the vertex source code
     * @param fragment_shader the fragment source code
     * @return the GL shader object
     */
    u32 create_shader(const std::string &vertex_shader,
                      const std::string &fragment_shader,
                      const std::string &geometry_shader);

    u32 id;
    std::unordered_map<std::string, i32> uniform_loc_cache;
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
