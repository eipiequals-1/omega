#ifndef _LIBGL2D_GFX_VERTEXBUFFER_H_
#define _LIBGL2D_GFX_VERTEXBUFFER_H_

#include <GL/gl.h>

namespace libgl {

/**
 * A Vertex Buffer provides methods for adding / storing vertex data such as position, normal, vector, color, etc to the GPU.
 * Holds a vertex attribute in the buffer
 */
class VertexBuffer {
   public:
	VertexBuffer(const void *data, uint32_t size);
	explicit VertexBuffer(GLsizeiptr size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	/**
	 * Changes the buffer's data.
	 * Range from offset to size must not overflow buffer
	 * @param offset in bytes
	 * @param size in bytes
	 * @param data data
	 */
	void SubData(GLintptr offset, GLsizeiptr size, const GLvoid *data);

   private:
	uint32_t id_;
};
}  // namespace libgl

#endif  // _LIBGL2D_GFX_VERTEXBUFFER_H_