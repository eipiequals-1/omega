#ifndef OMEGA_GFX_INDEXBUFFER_HPP
#define OMEGA_GFX_INDEXBUFFER_HPP

#include <cstddef>

#include "omega/util/types.hpp"

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
    static void unbind();

    /**
     * Returns the number of indices that are stored
     * which is passed as an argument to glDrawElements
     * @return the index count
     */
    u32 get_count() const {
        return count;
    }

    /**
     * Changes the buffer's data.
     * Range from offset to size must not overflow buffer
     * @param offset in bytes
     * @param size in bytes
     * @param data data
     */
    void sub_data(size_t offset, size_t size, const void *data);

  private:
    u32 id;
    u32 count;
};

} // namespace omega::gfx

#endif // OMEGA_GFX_INDEXBUFFER_HPP
