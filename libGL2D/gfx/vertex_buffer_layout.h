#ifndef LIBGL2D_GFX_VERTEXBUFFERLAYOUT_H
#define LIBGL2D_GFX_VERTEXBUFFERLAYOUT_H

#include <GL/gl.h>

#include <vector>

namespace libgl {

/**
 * A Vertex Buffer Attrib holds basic data about a single vertex attribute.
 * Holds easy access to data from the Vertex Buffer Layout
 */
struct VertexBufferAttrib {
	uint32_t type;   // data type: GL_FLOAT, GL_UNSIGNED_INT, etc
	uint32_t count;  // number of elements in this attribute
	unsigned char normalized;

	/**
	 * @param type the GLenum type of data
	 * @return the size of the data in bytes
	 */
	static uint32_t GetSizeOfType(uint32_t type) {
		switch (type) {
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		}
		return 0;
	}
};

/**
 * A Vertex Buffer Layout is a wrapper for an OpenGL vertex.
 * It sets the data (stride, elements) necessary to add to a Vertex Buffer.
 */
class VertexBufferLayout {
   public:
	VertexBufferLayout();

	/**
	 * Add a vertex attribute
	 * @param attrib_type type of data GL_FLOAT, GL_UNSIGNED_INT, etc
	 * @param count number of data to push
	 */
	void Push(uint32_t attrib_type, uint32_t count) {
		attributes_.push_back({attrib_type, count, GL_FALSE});
		stride_ += VertexBufferAttrib::GetSizeOfType(attrib_type) * count;
	}

	/**
	 * @returns the vector of vertex attributes
	 */
	const std::vector<VertexBufferAttrib> &GetAttributes() const { return attributes_; }

	/**
	 * @returns the stride of each vertex
	 */
	uint32_t GetStride() const { return stride_; }

   private:
	std::vector<VertexBufferAttrib> attributes_;
	uint32_t stride_;  // space between this vertex and next vertex
};

}  // namespace libgl

#endif  // LIBGL2D_GFX_VERTEXBUFFERLAYOUT_H