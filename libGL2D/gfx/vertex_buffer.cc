#include "vertex_buffer.h"

#include <GL/gl.h>

namespace libGL2D {

VertexBuffer::VertexBuffer(const void *data, uint32_t size) {
	glGenBuffers(1, &id_);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(GLsizeiptr size) {
	glGenBuffers(1, &id_);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &id_);
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SubData(GLintptr offset, GLsizeiptr size, const GLvoid *data) {
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

}  // namespace libGL2D
