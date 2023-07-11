#ifndef OMEGA_GFX_SPRITEBATCH_HPP
#define OMEGA_GFX_SPRITEBATCH_HPP

#include <array>
#include <cstring>
#include <memory>
#include <vector>

#include "omega/gfx/gl.hpp"
#include "omega/gfx/index_buffer.hpp"
#include "omega/gfx/shader.hpp"
#include "omega/gfx/texture/texture.hpp"
#include "omega/gfx/texture/texture_region.hpp"
#include "omega/gfx/vertex_array.hpp"
#include "omega/gfx/vertex_buffer.hpp"
#include "omega/gfx/vertex_buffer_layout.hpp"
#include "omega/math/math.hpp"
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
    void set_view_projection_matrix(const math::mat4 &view_proj) {
        sprite_shader->bind();
        sprite_shader->set_uniform_mat4f("u_ViewProjMatrix", view_proj);
        sprite_shader->unbind();
    }

    /**
     * Begins the rendering process
     */
    void begin_render();

    /**
     * Ends the rendering process and draws every quad from begin_render()
     * to the screen
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
    void render_texture(const Texture *texture,
                        const f32 x, const f32 y,
                        const math::vec4 &color = math::vec4(1.0f));

    /**
     * draw the given texture at the x, y, w, h coords and may resize as necessary
     * @param texture the texture to draw
     * @param x coord in world units
     * @param y coord in world units
     * @param w size in world units
     * @param h size in world units
     * @param color tint of the texture
     */
    void render_texture(const Texture *texture,
                        const f32 x, const f32 y,
                        const f32 w, const f32 h,
                        const math::vec4 &color = math::vec4(1.0f));

    /**
     * draw the given part of the texture to the destination
     * @param texture the texture to draw
     * @param src subrectangle of texture to draw in pixel units
     * @param dest the model matrix of the object
     * @param color tint of the texture
     */
    void render_texture(const Texture *texture,
                        const math::rectf &src,
                        const math::rectf &dest,
                        const math::vec4 &color = math::vec4(1.0f));

    /**
     * draw the given part of the texture to the destination
     * @param texture the texture to draw
     * @param src subrectangle of texture to draw in pixel units
     * @param dest the location of the rectangle in world coords
     * @param rotation in degrees counterclockwise
     * @param center center of rotation in world coordinates
     * @param color tint of the texture
     */
    void render_texture(const Texture *texture,
                        math::rectf src,
                        const math::rectf &dest,
                        f32 rotation,
                        const math::vec2 &center,
                        const math::vec4 &color = math::vec4(1.0f));

    void render_texture(const Texture *texture,
                        math::rectf src,
                        const math::rectf &dest,
                        const math::vec3 rotation_axis,
                        f32 rotation,
                        const math::vec3 &center_of_rotation,
                        const math::vec4 &color = math::vec4(1.0f));

    void render_texture_region(const TextureRegion *texture_region,
                               const math::rectf &dest,
                               const math::vec4 &color = math::vec4(1.0f));

  private:
    uptr<Shader> sprite_shader = nullptr;

    // buffers and gl objects
    uptr<VertexBuffer> vbo = nullptr;
    uptr<VertexArray> vao = nullptr;
    uptr<IndexBuffer> ibo = nullptr;

    // buffer constants
    static constexpr u32 quad_capacity = 1500;
    static constexpr u32 index_buffer_capacity = quad_capacity * 6;
    static constexpr u32 vertex_buffer_capacity = quad_capacity * 4;
    static constexpr u32 vertex_count = 17;
    static constexpr u32 index_count = 6;

    // texture data
    static constexpr u32 max_textures = 32;
    std::array<u32, max_textures> texture_binds;
    std::array<const Texture *, max_textures> textures_to_render;

    // render attributes
    u32 quads_rendered = 0;
    u32 tex_bind_slot = 0;

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
        math::vec3 position{0.0f};
        math::vec4 color{0.0f};
        math::vec2 tex_coords{0.0f};
        f32 tex_id = 0.0f;
        math::vec3 rotation_axis{0.0f};
        f32 rotation_angle = 0.0f;
        math::vec3 center_of_rot{0.0f};
    };

    // represents one texture / rectangle that is passed to the sprite shader
    using Quad = std::array<Vertex, 4>;

};

} // namespace omega::gfx

#endif // OMEGA_GFX_SPRITEBATCH_HPP
