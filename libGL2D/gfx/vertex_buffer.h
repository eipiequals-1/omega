#ifndef LIBGL2D_GFX_VERTEXBUFFER_H
#define LIBGL2D_GFX_VERTEXBUFFER_H

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

	/**
	 * Binds the Vertex Buffer in the OpenGL state machine
	 */
	void Bind() const;

	/**
	 * Unbinds the Vertex Buffer in the OpenGL state machine
	 */
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

#endif  // LIBGL2D_GFX_VERTEXBUFFER_H