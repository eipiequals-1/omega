#ifndef OMEGA_GFX_VERTEXARRAY_H
#define OMEGA_GFX_VERTEXARRAY_H

#include <vector>

#include "omega/gfx/vertex_buffer.h"
#include "omega/gfx/vertex_buffer_layout.h"

namespace omega {

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

	/**
	 * Binds the Vertex Array in the OpenGL state machine
	 */
	void Bind() const;

	/**
	 * Unbinds the Vertex Array in the OpenGL state machine
	 */
	void Unbind() const;

   private:
	uint32_t id_;
};

}  // namespace omega

#endif  // OMEGA_GFX_VERTEXARRAY_H