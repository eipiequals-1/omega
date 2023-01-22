#ifndef OMEGA_GFX_GL_H
#define OMEGA_GFX_GL_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "omega/util/math.hpp"

#include <iostream>

namespace omega::gfx {

/**
 * Creates the glViewport on the current framebuffer
 * @param x
 * @param y
 * @param width
 * @param height
 */
inline void viewport(int x, int y, uint32_t width, uint32_t height) {
    glViewport(x, y, width, height);
}

/**
 * Logs all OpenGL errors
 * @return if there were errors
 */
inline bool check_error() {
    int count = 0;
    GLenum error = glGetError();
    while (error != GL_NO_ERROR) {
        std::cout << "[OpenGL Error] (" << error << ": " << gluErrorString(error) << ")" << std::endl;
        error = glGetError();
        count++;
    }
    return count > 0;
}

/**
 * Clear the current frame buffer with the current clear color
 * @param mask
 */
inline void clear_buffer(GLbitfield mask = GL_COLOR_BUFFER_BIT) {
    glClear(mask);
}

/**
 * Set the clear color with normalized rgba params
 */
inline void set_clear_color(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

/**
 * Set the clear color with normalized params
 */
inline void set_clear_color(const glm::vec4 &color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

/**
 * @param b if the depth test should be on
 */
inline void set_depth_test(bool b) {
    if (b) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

/**
 * Enables blending for OpenGL
 * @param sfactor (default = GL_SRC_ALPHA)
 * @param dfactor (default = GL_ONE_MINUS_SRC_ALPHA)
 */
inline void enable_blending(GLenum sfactor = GL_SRC_ALPHA, GLenum dfactor = GL_ONE_MINUS_SRC_ALPHA) {
    glEnable(GL_BLEND);
    glBlendFunc(sfactor, dfactor);
}

/**
 * Calls glDrawArrays
 * @param render_type
 * @param start
 * @param count
 */
inline void draw_arrays(GLenum render_type, uint32_t start, uint32_t count) {
    glDrawArrays(render_type, start, count);
}

/**
 * Calss glDrawElements
 * @param mode render mode (i.e. GL_TRIANGLES)
 * @param count number of indices from index buffer
 * @param type type of indices (i.e. GL_UNSIGNED_INT)
 * @param indices pointer to the indices or if using IndexBuffer (nullptr)
 */
inline void draw_elements(GLenum mode, int32_t count, uint32_t type, const void *indices) {
    glDrawElements(mode, count, type, indices);
}

} // namespace omega::gfx

#endif // OMEGA_GFX_GL_H
