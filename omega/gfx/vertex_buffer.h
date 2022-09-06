#ifndef OMEGA_GFX_VERTEXBUFFER_H
#define OMEGA_GFX_VERTEXBUFFER_H

#include "omega/util/util.h"
#include <GL/gl.h>

namespace omega::gfx {

/**
 * A Vertex Buffer provides methods for adding / storing vertex data such as position, normal, vector, color, etc to the GPU.
 * Holds a vertex attribute in the buffer
 */
class VertexBuffer {
  public:
    VertexBuffer(const void *data, u32 size);
    explicit VertexBuffer(GLsizeiptr size);
    ~VertexBuffer();

    /**
     * Binds the Vertex Buffer in the OpenGL state machine
     */
    void bind() const;

    /**
     * Unbinds the Vertex Buffer in the OpenGL state machine
     */
    void unbind() const;

    /**
     * Changes the buffer's data.
     * Range from offset to size must not overflow buffer
     * @param offset in bytes
     * @param size in bytes
     * @param data data
     */
    void sub_data(GLintptr offset, GLsizeiptr size, const GLvoid *data);

  private:
    u32 id;
};
} // namespace omega::gfx

#endif // OMEGA_GFX_VERTEXBUFFER_H