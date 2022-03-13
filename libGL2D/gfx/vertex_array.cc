#include "vertex_array.h"

#include <GL/gl.h>

namespace libGL2D {

VertexArray::VertexArray() {
	glGenVertexArrays(1, &id_);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &id_);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();
	const auto& elements = layout.GetAttributes();
	uintptr_t offset = 0;
	for (uint32_t i = 0; i < elements.size(); ++i) {
		const auto& element = elements[i];
		// initialize attribute
		glEnableVertexAttribArray(i);
		// set pointer to data
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		// increase offset for pointer value
		offset += element.count * VertexBufferAttrib::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const {
	glBindVertexArray(id_);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}

}  // namespace libGL2D