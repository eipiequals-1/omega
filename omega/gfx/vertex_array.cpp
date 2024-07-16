#include "vertex_array.hpp"

#include "omega/gfx/gl.hpp"

namespace omega::gfx {

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id);
}

void VertexArray::add_buffer(const VertexBuffer &vb,
                             const VertexBufferLayout &layout) {
    bind();
    vb.bind();
    const auto &elements = layout.get_attributes();
    uintptr_t offset = 0;
    for (u32 i = 0; i < elements.size(); ++i) {
        const auto &element = elements[i];
        // initialize attribute
        glEnableVertexAttribArray(i);

        // set pointer to data
        if (element.type == GL_INT || element.type == GL_UNSIGNED_INT) {
            glVertexAttribIPointer(i,
                                   element.count,
                                   element.type,
                                   layout.get_stride(),
                                   (const void *)offset);
        } else {
            glVertexAttribPointer(i,
                                  element.count,
                                  element.type,
                                  element.normalized,
                                  layout.get_stride(),
                                  (const void *)offset);
        }
        // increase offset for pointer value
        offset +=
            element.count * VertexBufferAttrib::get_size_of_type(element.type);
    }
    unbind();
    vb.unbind();
}

void VertexArray::bind() const {
    glBindVertexArray(id);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

} // namespace omega::gfx
