#include "dfr.hpp"
#include "omega/gfx/frame_buffer.hpp"
#include "omega/gfx/gl.hpp"
#include "omega/gfx/vertex_array.hpp"
#include "omega/gfx/vertex_buffer.hpp"
#include "omega/gfx/vertex_buffer_layout.hpp"
#include "omega/util/std.hpp"

namespace omega::gfx::renderer {

DeferredRenderer::DeferredRenderer(
    u32 width, u32 height,
    const std::vector<FrameBufferAttachment> &attachments) {
    gbuffer = util::create_uptr<FrameBuffer>(width, height, attachments);

    // create composite quad
    const float vertices[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        1.0f, 1.0f,

        1.0f, 1.0f,
        -1.0f, 1.0f,
        -1.0f, -1.0f
    };
    vbo = util::create_uptr<VertexBuffer>(vertices, sizeof(vertices));
    vao = util::create_uptr<VertexArray>();

    VertexBufferLayout layout;
    layout.push(OMEGA_GL_FLOAT, 2);
    vao->add_buffer(*vbo, layout);
}

void DeferredRenderer::geometry_pass(
    std::function<void ()> render) {
    gbuffer->bind();
    render();
    gbuffer->unbind();
}

void DeferredRenderer::quad_pass(
    std::function<void ()> render) {
    render();

    vbo->bind();
    vao->bind();

    draw_arrays(OMEGA_GL_TRIANGLES, 0, 6);

    vbo->unbind();
    vao->unbind();
}

} // namespace omega::gfx::renderer
