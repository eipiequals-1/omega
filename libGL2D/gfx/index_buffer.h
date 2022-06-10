#ifndef _LIBGL2D_GFX_INDEXBUFFER_H_
#define _LIBGL2D_GFX_INDEXBUFFER_H_

#include <GL/gl.h>

namespace libgl {

/**
 * Wrapper for OpenGL Index Buffer Object
 * Stores the indices of vertices to render using glDrawElements
 */
class IndexBuffer {
   public:
	IndexBuffer(const uint32_t* data, uint32_t count);
	IndexBuffer(uint32_t count);
	~IndexBuffer();

	/**
	 * Binds the Index Buffer in the OpenGL state machine
	 */
	void Bind() const;

	/**
	 * Unbinds the Index Buffer in the OpenGl state machine
	 */
	void Unbind() const;

	/**
	 * Returns the number of indices that are stored
	 * which is passed as an argument to glDrawElements
	 * @return the index count
	 */
	GLint GetCount() const { return count_; }

	/**
	 * Changes the buffer's data.
	 * Range from offset to size must not overflow buffer
	 * @param offset in bytes
	 * @param size in bytes
	 * @param data data
	 */
	void SubData(GLintptr offset, GLsizeiptr size, const GLvoid* data);

   private:
	uint32_t id_;
	GLuint count_;
};

}  // namespace libgl

#endif  // _LIBGL2D_GFX_INDEXBUFFER_H_