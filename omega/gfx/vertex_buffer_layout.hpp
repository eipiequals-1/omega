#ifndef OMEGA_GFX_VERTEXBUFFERLAYOUT_HPP
#define OMEGA_GFX_VERTEXBUFFERLAYOUT_HPP

#include <vector>

#include "omega/util/types.hpp"

namespace omega::gfx {

/**
 * A Vertex Buffer Attrib holds basic data about a single vertex attribute.
 * Holds easy access to data from the Vertex Buffer Layout
 */
struct VertexBufferAttrib {
    u32 type;  // data type: GL_FLOAT, GL_UNSIGNED_INT, etc
    u32 count; // number of elements in this attribute
    unsigned char normalized;

    /**
     * @param type the GLenum type of data
     * @return the size of the data in bytes
     */
    static u32 get_size_of_type(u32 type);
};

/**
 * A Vertex Buffer Layout is a wrapper for an OpenGL vertex.
 * It sets the data (stride, elements) necessary to add to a Vertex Buffer.
 */
class VertexBufferLayout {
  public:
    VertexBufferLayout() = default;

    /**
     * Add a vertex attribute
     * @param attrib_type type of data GL_FLOAT, GL_UNSIGNED_INT, etc
     * @param count number of data to push
     */
    void push(u32 attrib_type, u32 count) {
        attributes.push_back({attrib_type, count, 0});
        stride += VertexBufferAttrib::get_size_of_type(attrib_type) * count;
    }

    /**
     * @returns the vector of vertex attributes
     */
    const std::vector<VertexBufferAttrib> &get_attributes() const {
        return attributes;
    }

    /**
     * @returns the stride of each vertex
     */
    u32 get_stride() const {
        return stride;
    }

  private:
    std::vector<VertexBufferAttrib> attributes;
    u32 stride = 0; // space between this vertex and next vertex
};

} // namespace omega::gfx

#endif // OMEGA_GFX_VERTEXBUFFERLAYOUT_HPP
