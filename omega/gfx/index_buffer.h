#ifndef OMEGA_GFX_INDEXBUFFER_H
#define OMEGA_GFX_INDEXBUFFER_H

#include "omega/util/util.h"
#include <GL/gl.h>

namespace omega::gfx {

/**
 * Wrapper for OpenGL Index Buffer Object
 * Stores the indices of vertices to render using glDrawElements
 */
class IndexBuffer {
  public:
    IndexBuffer(const u32 *data, u32 count);
    IndexBuffer(u32 count);
    ~IndexBuffer();

    /**
     * Binds the Index Buffer in the OpenGL state machine
     */
    void bind() const;

    /**
     * Unbinds the Index Buffer in the OpenGl state machine
     */
    void unbind() const;

    /**
     * Returns the number of indices that are stored
     * which is passed as an argument to glDrawElements
     * @return the index count
     */
    GLuint get_count() const { return count; }

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
    GLuint count;
};

} // namespace omega::gfx

#endif // OMEGA_GFX_INDEXBUFFER_H