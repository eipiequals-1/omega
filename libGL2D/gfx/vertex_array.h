#ifndef _LIBGL2D_GFX_VERTEXARRAY_H_
#define _LIBGL2D_GFX_VERTEXARRAY_H_

#include <vector>

#include "libGL2D/gfx/vertex_buffer.h"
#include "libGL2D/gfx/vertex_buffer_layout.h"

namespace libGL2D {

/**
 * A Vertex Array stores all of the data to supply a vertex. This implementation holds Vertex Buffers as a wrapper for the vertex attributes
 */
class VertexArray {
   public:
	VertexArray();
	~VertexArray();

	/**
	 * Sets the vertex attributes in the OpenGL vertexArray
	 * @param vb Buffer to bind vertex attributes to
	 * @param layout information about attributes
	 */
	void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

	void Bind() const;
	void Unbind() const;

   private:
	uint32_t id_;
};

}  // namespace libGL2D

#endif  // _LIBGL2D_GFX_VERTEXARRAY_H_