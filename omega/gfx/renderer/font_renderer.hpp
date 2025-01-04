#ifndef OMEGA_GFX_RENDERER_FONTRENDERER_HPP
#define OMEGA_GFX_RENDERER_FONTRENDERER_HPP

#include "omega/gfx/gl.hpp"
#include "omega/gfx/shader.hpp"
#include "omega/gfx/shaders/font.hpp"
#include "omega/gfx/vertex_array.hpp"
#include "omega/gfx/vertex_buffer.hpp"
#include "omega/ui/ttf.hpp"
#include "omega/util/color.hpp"
#include "omega/util/std.hpp"

namespace omega::gfx::renderer {

class FontRenderer {
  public:
    FontRenderer() {
        shader =
            util::create_uptr<Shader>(shaders::font_vert, shaders::font_frag);
        // create the Vertex buffer and array
        vbo = util::create_uptr<omega::gfx::VertexBuffer>(sizeof(Vertex) * 6 *
                                                          quad_count);
        vao = util::create_uptr<omega::gfx::VertexArray>();

        VertexBufferLayout layout;
        layout.push(OMEGA_GL_FLOAT, 2);
        layout.push(OMEGA_GL_FLOAT, 2);
        layout.push(OMEGA_GL_FLOAT, 4);
        vao->add_buffer(*vbo, layout);
    }

    void set_view_proj_matrix(const math::mat4 &vp) {
        shader->bind();
        shader->set_uniform_mat4f("u_view_proj", vp);
        shader->unbind();
    }

    void begin() {
        chars_rendered = 0;
    }

    void render(ui::TTFont *font,
                const std::string &text,
                math::vec2 pos,
                f32 height,
                const math::vec4 &color = util::color::white) {
        font->get_texture()->bind(0);

        Vertex vertices[6];
        f32 scale_factor = height / font->get_font_size();
        auto origin = pos;

        // iterate through the characters
        for (const auto &c : text) {
            if (c == '\n') {
                pos.y -= font->get_font_size() * scale_factor;
                pos.x = origin.x;
                continue;
            }
            const ui::Glyph &glyph = font->get_glyph(c);

            math::rectf src{(f32)glyph.tex_coords.x,
                            (f32)glyph.tex_coords.y,
                            (f32)glyph.size.x,
                            (f32)glyph.size.y};

            // normalize the src rectangle (texture coordinates)
            src.x = src.x / font->get_texture()->get_width();
            src.y = src.y / font->get_texture()->get_height();
            src.w = src.w / font->get_texture()->get_width();
            src.h = src.h / font->get_texture()->get_height();

            math::rectf dest{
                pos.x + glyph.offset.x * scale_factor,
                pos.y - (glyph.size.y - glyph.offset.y) * scale_factor,
                glyph.size.x * scale_factor,
                glyph.size.y * scale_factor};

            vertices[0] = {{dest.x, dest.y}, {src.x, src.y + src.h}, color};
            vertices[1] = {{dest.x + dest.w, dest.y},
                           {src.x + src.w, src.y + src.h},
                           color};
            vertices[2] = {{dest.x + dest.w, dest.y + dest.h},
                           {src.x + src.w, src.y},
                           color};
            vertices[3] = vertices[2];
            vertices[4] = {{dest.x, dest.y + dest.h}, {src.x, src.y}, color};
            vertices[5] = vertices[0];

            vbo->bind();
            vbo->sub_data(sizeof(Vertex) * 6 * chars_rendered,
                          sizeof(Vertex) * 6,
                          vertices);
            vbo->unbind();
            chars_rendered++;
            if (chars_rendered == quad_count) {
                end();
                begin();
            }

            pos.x += glyph.advance.x * scale_factor;
        }
    }

    void end() {
        shader->bind();
        vbo->bind();
        vao->bind();

        shader->set_uniform_1i("u_texture", 0);
        omega::gfx::draw_arrays(OMEGA_GL_TRIANGLES, 0, chars_rendered * 6);

        vao->unbind();
        vbo->unbind();
        shader->unbind();
    }

  private:
    struct Vertex {
        math::vec2 pos;
        math::vec2 tex_coords;
        math::vec4 color;
    };

    u32 quad_count = 500; // so we can draw lots of chars
    util::uptr<gfx::VertexBuffer> vbo = nullptr;
    util::uptr<gfx::VertexArray> vao = nullptr;
    util::uptr<gfx::Shader> shader = nullptr;

    u32 chars_rendered = 0;
};

} // namespace omega::gfx::renderer

#endif // OMEGA_GFX_RENDERER_FONTRENDERER_HPP
