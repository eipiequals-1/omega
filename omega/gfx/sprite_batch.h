#ifndef OMEGA_GFX_SPRITEBATCH_H
#define OMEGA_GFX_SPRITEBATCH_H

#include <GL/gl.h>

#include <cstring>
#include <memory>
#include <vector>

#include "omega/gfx/index_buffer.h"
#include "omega/gfx/shader.h"
#include "omega/gfx/texture/texture.h"
#include "omega/gfx/texture/texture_region.h"
#include "omega/gfx/vertex_array.h"
#include "omega/gfx/vertex_buffer.h"
#include "omega/gfx/vertex_buffer_layout.h"
#include "omega/util/util.h"

namespace omega::gfx {

using namespace omega::util;
using namespace omega::gfx::texture;

/**
 * Represents a SpriteBatch Vertex with:
 * position,
 * color,
 * texture id,
 * rotation,
 * center of rotation
 */
struct Vertex {
    f32 position[2];
    f32 color[4];
    f32 texCoords[2];
    f32 tex_id;
    f32 rotation;
    f32 center_of_rot[2];
};

// represents one texture / rectangle that is passed to the sprite shader
using Quad = std::array<Vertex, 4>;

/**
 * Renders hundreds-thousands of quads in a single draw call
 * for faster rendering.
 * For even more optimization, a TextureAtlas is recommended
 * to minimize the number of slots in a draw call
 */
class SpriteBatch {
  public:
    SpriteBatch(const SpriteBatch &) = delete;
    SpriteBatch operator=(const SpriteBatch &) = delete;

    virtual ~SpriteBatch();

    static SpriteBatch &instance() {
        static SpriteBatch batch;
        return batch;
    }

    /**
     * Sets the view and projection matrices typically from the camera object
     * representing the game world
     * Must be called before rendering and on each frame if the camera changes
     * @param projection the view projection Matrix
     */
    virtual void set_view_projection_matrix(const glm::mat4 &view_proj) {
        sprite_shader->bind();
        sprite_shader->set_uniform_mat4f("u_ViewProjMatrix", view_proj);
        sprite_shader->unbind();
    }

    /**
     * Begins the rendering process
     */
    virtual void begin_render();

    /**
     * Ends the rendering process and draws every quad from Beginrender() to the screen
     * in one draw call
     */
    virtual void end_render();

    /**
     * draw the given texture at the x, y coords
     * @param texture the texture to draw
     * @param x coord in world units
     * @param y coord in world units
     * @param color tint of the texture
     */
    virtual void render_texture(const Texture *texture, const f32 x, const f32 y, const glm::vec4 &color = glm::vec4(1.0f));

    /**
     * draw the given texture at the x, y, w, h coords and may resize as necessary
     * @param texture the texture to draw
     * @param x coord in world units
     * @param y coord in world units
     * @param w size in world units
     * @param h size in world units
     * @param color tint of the texture
     */
    virtual void render_texture(const Texture *texture, const f32 x, const f32 y, const f32 w, const f32 h, const glm::vec4 &color = glm::vec4(1.0f));

    /**
     * draw the given part of the texture to the destination
     * @param texture the texture to draw
     * @param src subrectangle of texture to draw in pixel units
     * @param dest the model matrix of the object
     * @param color tint of the texture
     */
    virtual void render_texture(const Texture *texture, const glm::rectf &src, const glm::rectf &dest, const glm::vec4 &color = glm::vec4(1.0f));

    /**
     * draw the given part of the texture to the destination
     * @param texture the texture to draw
     * @param src subrectangle of texture to draw in pixel units
     * @param dest the model matrix of the object
     * @param rotation in degrees counterclockwise
     * @param center center of rotation in world coordinates
     * @param color tint of the texture
     */
    virtual void render_texture(const Texture *texture, glm::rectf src, const glm::rectf &dest, f32 rotation, const glm::vec2 &center, const glm::vec4 &color = glm::vec4(1.0f));

    virtual void render_texture_region(const TextureRegion *texture_region, const glm::rectf &dest, const glm::vec4 &color = glm::vec4(1.0f));

  protected:
    uptr<Shader> sprite_shader;
    uptr<VertexBuffer> vbo;
    uptr<VertexArray> vao;
    uptr<IndexBuffer> ibo;
    // buffer constants
    static constexpr u32 kQuadCapacity = 1500;
    static constexpr u32 kIndexBufferCapacity = kQuadCapacity * 6;
    static constexpr u32 kVertexBufferCapacity = kQuadCapacity * 4;
    static constexpr u32 kVertexCount = 12;
    static constexpr u32 kIndexCount = 6;
    // texture data
    static constexpr u32 kMaxTextures = 32;
    std::array<u32, kMaxTextures> texture_binds;
    std::array<const Texture *, kMaxTextures> textures_to_render;

    // render attributes
    u32 quads_rendered;
    u32 tex_bind_slot;

  private:
    SpriteBatch();
};

} // namespace omega::gfx

#endif // OMEGA_GFX_SPRITEBATCH_H