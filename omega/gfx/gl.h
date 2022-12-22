#ifndef OMEGA_GFX_GL_H
#define OMEGA_GFX_GL_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>

namespace omega::gfx {

inline void viewport(int x, int y, uint32_t width, uint32_t height) {
    glViewport(x, y, width, height);
}

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

inline void set_clear_color(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

inline void enable_depth_test() {
    glEnable(GL_DEPTH_TEST);
}

inline void enable_blending(GLenum sfactor = GL_SRC_ALPHA, GLenum dfactor = GL_ONE_MINUS_SRC_ALPHA) {
    glEnable(GL_BLEND);
    glBlendFunc(sfactor, dfactor);
}

inline void draw_arrays(GLenum render_type, uint32_t start, uint32_t count) {
    glDrawArrays(render_type, start, count);
}

inline void draw_elements(GLenum mode, int32_t count, uint32_t type, const void *indices) {
    glDrawElements(mode, count, type, indices);
}

} // namespace omega::gfx

#endif // OMEGA_GFX_GL_H