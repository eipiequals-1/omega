#include "index_buffer.h"

#include <GL/gl.h>

namespace omega {

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count) : count_(count) {
	glGenBuffers(1, &id_);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(uint32_t count) : count_(count) {
	glGenBuffers(1, &id_);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &id_);
}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void IndexBuffer::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::SubData(GLintptr offset, GLsizeiptr size, const GLvoid* data) {
	Bind();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}

}  // namespace omega
