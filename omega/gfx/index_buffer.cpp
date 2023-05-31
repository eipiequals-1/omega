#include "index_buffer.hpp"

#include "omega/gfx/gl.hpp"

namespace omega::gfx {

IndexBuffer::IndexBuffer(const u32 *data, u32 count) : count(count) {
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32),
                 data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(u32 count) : count(count) {
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32),
                 nullptr, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &id);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::sub_data(size_t offset, size_t size, const void *data) {
    bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}

} // namespace omega::gfx
