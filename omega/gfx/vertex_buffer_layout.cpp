#include "vertex_buffer_layout.hpp"

#include "omega/gfx/gl.hpp"

namespace omega::gfx {

uint32_t VertexBufferAttrib::get_size_of_type(uint32_t type) {
    switch (type) {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
    }
    return 0;
}

}
