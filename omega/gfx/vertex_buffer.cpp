#include "vertex_buffer.hpp"

#include "omega/gfx/gl.hpp"

namespace omega::gfx {

VertexBuffer::VertexBuffer(const void *data, uint32_t size) {
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    std::cout << size << "   " << id << "   \n";
}

VertexBuffer::VertexBuffer(size_t size) {
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    std::cout << size << "   " << id << "   \n";
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::sub_data(size_t offset, size_t size, const void *data) {
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

} // namespace omega::gfx
