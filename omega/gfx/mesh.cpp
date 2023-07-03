#include "mesh.hpp"

#include "omega/util/std.hpp"

namespace omega::gfx {

Mesh::Mesh(size_t size, const VertexBufferLayout &layout) {
    vao = util::create_uptr<VertexArray>();
    vbo = util::create_uptr<VertexBuffer>(size);
    vao->add_buffer(*vbo, layout);
}

void Mesh::render(Shader &shader, macro primitive) {
    shader.bind();
    vao->bind();
    if (ibo != nullptr) {
        ibo->bind();
        draw_elements(primitive, ibo->get_count(), GL_UNSIGNED_INT, nullptr);
        IndexBuffer::unbind();
    } else {
        draw_arrays(primitive, 0, num_vertices);
    }

    VertexArray::unbind();
    Shader::unbind();
}

} // namespace omega::gfx
