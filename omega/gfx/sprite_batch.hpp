#ifndef OMEGA_GFX_SPRITEBATCH_HPP
#define OMEGA_GFX_SPRITEBATCH_HPP

#include <array>
#include <cstring>
#include <memory>
#include <vector>

/* #include "omega/gfx/gl.hpp" */
#include "omega/gfx/index_buffer.hpp"
#include "omega/gfx/shader.hpp"
#include "omega/gfx/texture/texture.hpp"
#include "omega/gfx/texture/texture_region.hpp"
#include "omega/gfx/vertex_array.hpp"
#include "omega/gfx/vertex_buffer.hpp"
#include "omega/gfx/vertex_buffer_layout.hpp"
#include "omega/util/math.hpp"
#include "omega/util/std.hpp"

namespace omega::gfx {

using namespace omega::util;
using namespace omega::gfx::texture;

/**
 * Renders hundreds-thousands of quads in a single draw call
 * for faster rendering.
 * For even more optimization, a TextureAtlas is recommended
 * to minimize the number of slots in a draw call
 */
class SpriteBatch {
  public:
    SpriteBatch();
   ~SpriteBatch() = default;

    /**
     * Sets the view and projection matrices typically from the camera object
     * representing the game world
     * Must be called before rendering and on each frame if the camera changes
     * @param projection the view projection Matrix
     */
    void set_view_projection_matrix(const glm::mat4 &view_proj) {
        sprite_shader->bind();
        sprite_shader->set_uniform_mat4f("u_ViewProjMatrix", view_proj);
        sprite_shader->unbind();
    }

    /**
     * Begins the rendering process
     */
    void begin_render();

    /**
     * Ends the rendering process and draws every quad from Beginrender() to the screen
     * in one draw call
     */
    void end_render();

    /**
     * draw the given texture at the x, y coords
     * @param texture the texture to draw
     * @param x coord in world units
     * @param y coord in world units
     * @param color tint of the texture
     */
    void render_texture(const Texture *texture, const float x, const float y, const glm::vec4 &color = glm::vec4(1.0f));

    /**
     * draw the given texture at the x, y, w, h coords and may resize as necessary
     * @param texture the texture to draw
     * @param x coord in world units
     * @param y coord in world units
     * @param w size in world units
     * @param h size in world units
     * @param color tint of the texture
     */
    void render_texture(const Texture *texture, const float x, const float y, const float w, const float h, const glm::vec4 &color = glm::vec4(1.0f));

    /**
     * draw the given part of the texture to the destination
     * @param texture the texture to draw
     * @param src subrectangle of texture to draw in pixel units
     * @param dest the model matrix of the object
     * @param color tint of the texture
     */
    void render_texture(const Texture *texture, const glm::rectf &src, const glm::rectf &dest, const glm::vec4 &color = glm::vec4(1.0f));

    /**
     * draw the given part of the texture to the destination
     * @param texture the texture to draw
     * @param src subrectangle of texture to draw in pixel units
     * @param dest the location of the rectangle in world coords
     * @param rotation in degrees counterclockwise
     * @param center center of rotation in world coordinates
     * @param color tint of the texture
     */
    void render_texture(const Texture *texture, glm::rectf src, const glm::rectf &dest, float rotation, const glm::vec2 &center, const glm::vec4 &color = glm::vec4(1.0f));

    void render_texture(const Texture *texture, glm::rectf src, const glm::rectf &dest, const glm::vec3 rotation_axis, float rotation, const glm::vec3 &center_of_rotation, const glm::vec4 &color = glm::vec4(1.0f));

    void render_texture_region(const TextureRegion *texture_region, const glm::rectf &dest, const glm::vec4 &color = glm::vec4(1.0f));

  private:
    uptr<Shader> sprite_shader = nullptr;

    // buffers and gl objects
    uptr<VertexBuffer> vbo = nullptr;
    uptr<VertexArray> vao = nullptr;
    uptr<IndexBuffer> ibo = nullptr;

    // buffer constants
    static constexpr uint32_t quad_capacity = 1500;
    static constexpr uint32_t index_buffer_capacity = quad_capacity * 6;
    static constexpr uint32_t vertex_buffer_capacity = quad_capacity * 4;
    static constexpr uint32_t vertex_count = 17;
    static constexpr uint32_t index_count = 6;

    // texture data
    static constexpr uint32_t max_textures = 32;
    std::array<uint32_t, max_textures> texture_binds;
    std::array<const Texture *, max_textures> textures_to_render;

    // render attributes
    uint32_t quads_rendered = 0;
    uint32_t tex_bind_slot = 0;

    /**
     * Represents a SpriteBatch Vertex with:
     * position,
     * color,
     * texture coords,
     * texture id,
     * rotation axis,
     * rotation angle,
     * center of rotation
     */
    struct Vertex {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 tex_coords;
        float tex_id;
        glm::vec3 rotation_axis;
        float rotation_angle;
        glm::vec3 center_of_rot;
    };

    // represents one texture / rectangle that is passed to the sprite shader
    using Quad = std::array<Vertex, 4>;

};

} // namespace omega::gfx

#endif // OMEGA_GFX_SPRITEBATCH_HPP
