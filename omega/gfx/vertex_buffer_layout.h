#ifndef OMEGA_GFX_VERTEXBUFFERLAYOUT_H
#define OMEGA_GFX_VERTEXBUFFERLAYOUT_H

#include <GL/gl.h>

#include "omega/util/util.h"
#include <vector>

namespace omega::gfx {

/**
 * A Vertex Buffer Attrib holds basic data about a single vertex attribute.
 * Holds easy access to data from the Vertex Buffer Layout
 */
struct VertexBufferAttrib {
    uint32_t type;  // data type: GL_FLOAT, GL_UNSIGNED_INT, etc
    uint32_t count; // number of elements in this attribute
    unsigned char normalized;

    /**
     * @param type the GLenum type of data
     * @return the size of the data in bytes
     */
    static uint32_t get_size_of_type(uint32_t type) {
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
};

/**
 * A Vertex Buffer Layout is a wrapper for an OpenGL vertex.
 * It sets the data (stride, elements) necessary to add to a Vertex Buffer.
 */
class VertexBufferLayout {
  public:
    VertexBufferLayout();

    /**
     * Add a vertex attribute
     * @param attrib_type type of data GL_FLOAT, GL_UNSIGNED_INT, etc
     * @param count number of data to push
     */
    void push(uint32_t attrib_type, uint32_t count) {
        attributes.push_back({attrib_type, count, GL_FALSE});
        stride += VertexBufferAttrib::get_size_of_type(attrib_type) * count;
    }

    /**
     * @returns the vector of vertex attributes
     */
    const std::vector<VertexBufferAttrib> &get_attributes() const { return attributes; }

    /**
     * @returns the stride of each vertex
     */
    uint32_t get_stride() const { return stride; }

  private:
    std::vector<VertexBufferAttrib> attributes;
    uint32_t stride; // space between this vertex and next vertex
};

} // namespace omega::gfx

#endif // OMEGA_GFX_VERTEXBUFFERLAYOUT_H