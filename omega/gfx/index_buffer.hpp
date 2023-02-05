#ifndef OMEGA_GFX_INDEXBUFFER_H
#define OMEGA_GFX_INDEXBUFFER_H

#include <cstdint>
#include <cstddef>

namespace omega::gfx {

/**
 * Wrapper for OpenGL Index Buffer Object
 * Stores the indices of vertices to render using glDrawElements
 */
class IndexBuffer {
  public:
    IndexBuffer(const uint32_t *data, uint32_t count);
    IndexBuffer(uint32_t count);
    ~IndexBuffer();

    /**
     * Binds the Index Buffer in the OpenGL state machine
     */
    void bind() const;

    /**
     * Unbinds the Index Buffer in the OpenGl state machine
     */
    static void unbind();

    /**
     * Returns the number of indices that are stored
     * which is passed as an argument to glDrawElements
     * @return the index count
     */
    uint32_t get_count() const { return count; }

    /**
     * Changes the buffer's data.
     * Range from offset to size must not overflow buffer
     * @param offset in bytes
     * @param size in bytes
     * @param data data
     */
    void sub_data(size_t offset, size_t size, const void *data);

  private:
    uint32_t id;
    uint32_t count;
};

} // namespace omega::gfx

#endif // OMEGA_GFX_INDEXBUFFER_H
