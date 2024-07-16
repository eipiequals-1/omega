#include "sprite_batch.hpp"

#include <algorithm>
#include <iostream>
#include <memory>

#include "omega/gfx/gl.hpp"
#include "omega/gfx/shaders/sb.hpp"

namespace omega::gfx {

SpriteBatch::SpriteBatch() {
    // indices will never change so set them now
    u32 indices[index_buffer_capacity];
    u32 offset = 0;
    for (size_t i = 0; i < index_buffer_capacity; i += 6) {
        // triangle 1
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;
        // triangle 2
        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 0 + offset;

        offset += 4;
    }
    ibo = create_uptr<IndexBuffer>(indices, index_buffer_capacity);

#ifdef EMSCRIPTEN
    sprite_shader =
        create_uptr<Shader>(shaders::sb_vert_wasm, shaders::sb_frag_wasm);
#else
    sprite_shader = create_uptr<Shader>(shaders::sb_vert, shaders::sb_frag);
#endif

    vao = create_uptr<VertexArray>();
    vbo = create_uptr<VertexBuffer>(vertex_buffer_capacity * vertex_count *
                                    sizeof(f32));

    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 3); // world coords
    layout.push(GL_FLOAT, 4); // color
    layout.push(GL_FLOAT, 2); // tex coords
    layout.push(GL_FLOAT, 1); // tex idx
    layout.push(GL_FLOAT, 3); // rotation axis
    layout.push(GL_FLOAT, 1); // rotation angle
    layout.push(GL_FLOAT, 3); // rotation center
    vao->add_buffer(*vbo, layout);

    for (u32 i = 0; i < max_textures; ++i) {
        texture_binds[i] = i;
    }
    sprite_shader->bind();
    sprite_shader->set_uniform_1iv(
        "u_Textures", (int *)texture_binds.data(), max_textures);
    Shader::unbind();
}

void SpriteBatch::begin_render() {
    quads_rendered = 0;
    tex_bind_slot = 0;
    // reset previous batch texture data
    for (size_t i = 0; i < textures_to_render.size(); i++) {
        textures_to_render[i] = nullptr;
    }
    sprite_shader->bind();
}

void SpriteBatch::render_texture(const Texture *texture,
                                 const f32 x,
                                 const f32 y,
                                 const math::vec4 &color) {
    render_texture(
        texture, x, y, texture->get_width(), texture->get_height(), color);
}

void SpriteBatch::render_texture(const Texture *texture,
                                 const f32 x,
                                 const f32 y,
                                 const f32 w,
                                 const f32 h,
                                 const math::vec4 &color) {
    // set tex coords
    math::rectf tex_coords(
        0.0f, 0.0f, texture->get_width(), texture->get_height());
    render_texture(texture, tex_coords, math::rectf(x, y, w, h), color);
}

void SpriteBatch::render_texture(const Texture *texture,
                                 const math::rectf &src,
                                 const math::rectf &dest,
                                 const math::vec4 &color) {
    render_texture(texture, src, dest, 0.0f, dest.center(), color);
}

void SpriteBatch::render_texture(const Texture *texture,
                                 math::rectf src,
                                 const math::rectf &dest,
                                 f32 rotation,
                                 const math::vec2 &center,
                                 const math::vec4 &color) {
    render_texture(texture,
                   src,
                   dest,
                   math::vec3(0.0f, 0.0f, -1.0f),
                   rotation,
                   math::vec3(center, 0.0f),
                   color);
}

void SpriteBatch::render_texture(const Texture *texture,
                                 math::rectf src,
                                 const math::rectf &dest,
                                 const math::vec3 rotation_axis,
                                 f32 rotation,
                                 const math::vec3 &center_of_rotation,
                                 const math::vec4 &color) {
    if (quads_rendered == quad_capacity) {
        end_render();
        begin_render();
    }
    f32 tex_id = tex_bind_slot;
    // check if texture has been used in this batch
    bool in_batch = false;
    for (u32 i = 0; i < textures_to_render.size(); i++) {
        if (textures_to_render[i] == texture) {
            in_batch = true;
            tex_id = i;
            break;
        }
    }
    if (!in_batch) {
        if (tex_bind_slot == max_textures) {
            end_render();
            begin_render();
        }
        // add the texture to the to render vector and bind
        textures_to_render[tex_bind_slot] = texture;
        texture->bind(tex_bind_slot);
        tex_id = tex_bind_slot;
        tex_bind_slot++;
    }
    // normalize src rect
    src.x = src.x / texture->get_width();
    src.y = src.y / texture->get_height();
    src.w = src.w / texture->get_width();
    src.h = src.h / texture->get_height();
    constexpr static f32 z = 0.0f;

    // inverse texture to y up
    Vertex v0 = {{dest.x, dest.y, z},
                 color,
                 {src.x, src.y + src.h},
                 tex_id,
                 rotation_axis,
                 rotation,
                 center_of_rotation};
    Vertex v1 = {{dest.x + dest.w, dest.y, z},
                 color,
                 {src.x + src.w, src.y + src.h},
                 tex_id,
                 rotation_axis,
                 rotation,
                 center_of_rotation};
    Vertex v2 = {{dest.x + dest.w, dest.y + dest.h, z},
                 color,
                 {src.x + src.w, src.y},
                 tex_id,
                 rotation_axis,
                 rotation,
                 center_of_rotation};
    Vertex v3 = {{dest.x, dest.y + dest.h, z},
                 color,
                 {src.x, src.y},
                 tex_id,
                 rotation_axis,
                 rotation,
                 center_of_rotation};

    Quad q = {v0, v1, v2, v3};
    auto quad = q.data();

    vbo->bind();
    vbo->sub_data(sizeof(Quad) * quads_rendered, sizeof(Quad), quad);
    vbo->unbind();
    quads_rendered++;
}

void SpriteBatch::render_texture_region(const TextureRegion *texture_region,
                                        const math::rectf &dest,
                                        const math::vec4 &color) {
    render_texture(texture_region->get_texture(),
                   texture_region->get_rect().convert_type<f32>(),
                   dest,
                   color);
}

void SpriteBatch::end_render() {
    sprite_shader->bind();
    vao->bind();
    vbo->bind();
    ibo->bind();
    draw_elements(OMEGA_GL_TRIANGLES,
                  quads_rendered * index_count,
                  OMEGA_GL_UNSIGNED_INT,
                  nullptr);

    VertexArray::unbind();
    VertexBuffer::unbind();
    IndexBuffer::unbind();
    Shader::unbind();
}

} // namespace omega::gfx
