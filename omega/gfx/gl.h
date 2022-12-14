#ifndef OMEGA_GFX_GL_H
#define OMEGA_GFX_GL_H

#include <GL/gl.h>

#include "omega/util/types.h"

namespace omega::gfx {

enum class GLConstant {
    src_alpha = GL_SRC_ALPHA,
    one_minus_src_alpha = GL_ONE_MINUS_SRC_ALPHA
};

/**
 * Clear the current frame buffer with the current clear color
 * @param mask
 */
inline void clear_buffer(GLbitfield mask = GL_COLOR_BUFFER_BIT) {
    glClear(mask);
}

inline void set_clear_color(f32 r, f32 g, f32 b, f32 a) {
    glClearColor(r, g, b, a);
}

inline void enable_depth_test() {
    glEnable(GL_DEPTH_TEST);
}

inline void enable_blending(GLenum sfactor = GL_SRC_ALPHA, GLenum dfactor = GL_ONE_MINUS_SRC_ALPHA) {
    glEnable(GL_BLEND);
    glBlendFunc(sfactor, dfactor);
}

inline void draw_arrays(GLenum render_type, u32 start, u32 count) {
    glDrawArrays(render_type, start, count);
}

inline void draw_elements(GLenum mode, i32 count, u32 type, const void *indices) {
    glDrawElements(mode, count, type, indices);
}

} // namespace omega::gfx

#endif // OMEGA_GFX_GL_H