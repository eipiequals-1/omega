#ifndef OMEGA_GFX_GL_HPP
#define OMEGA_GFX_GL_HPP

#include "omega/core/platform.hpp"

#include <iostream>

#include "omega/util/math.hpp"
#include "omega/util/types.hpp"

// rename OpenGL macros
// clear screen macros
#define OMEGA_GL_COLOR_BUFFER_BIT GL_COLOR_BUFFER_BIT
#define OMEGA_GL_DEPTH_BUFFER_BIT GL_DEPTH_BUFFER_BIT
#define OMEGA_GL_STENCIL_BUFFER_BIT GL_STENCIL_BUFFER_BIT

#define OMEGA_GL_DEPTH_TEST GL_DEPTH_TEST
#define OMEGA_GL_SRC_ALPHA GL_SRC_ALPHA
#define OMEGA_GL_BLEND GL_BLEND
#define OMEGA_GL_ONE_MINUS_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA

// render modes
#define OMEGA_GL_TRIANGLES GL_TRIANGLES
#define OMEGA_GL_LINES GL_LINES
#define OMEGA_GL_TRIANGLE_STRIP GL_TRIANGLE_STRIP
#define OMEGA_GL_TRIANGLE_FAN GL_TRIANGLE_FAN

// rendering
#define OMEGA_GL_FALSE GL_FALSE
#define OMEGA_GL_TRUE GL_TRUE

// buffer information
#define OMEGA_GL_UNSIGNED_BYTE GL_UNSIGNED_BYTE
#define OMEGA_GL_UNSIGNED_SHORT GL_UNSIGNED_SHORT
#define OMEGA_GL_UNSIGNED_INT GL_UNSIGNED_INT
#define OMEGA_GL_FLOAT GL_FLOAT
#define OMEGA_GL_INT GL_INT

// textures
#define OMEGA_GL_NEAREST GL_NEAREST
#define OMEGA_GL_LINEAR GL_LINEAR

namespace omega::gfx {

using bitfield = GLbitfield;
using macro = GLenum;

/**
 * Creates the glViewport on the current framebuffer
 * @param x
 * @param y
 * @param width
 * @param height
 */
inline void viewport(i32 x, i32 y, u32 width, u32 height) {
    glViewport(x, y, width, height);
}

/**
 * Logs all OpenGL errors
 * @return if there were errors
 */
inline bool check_error() {
    int count = 0;
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::string error_string;
        switch (error) {
            case GL_INVALID_ENUM: error_string = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE: error_string = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:
                error_string = "INVALID_OPERATION"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error_string = "INVALID_FRAMEBUFFER_OPERATION"; break;
#ifndef EMSCRIPTEN
            case GL_INVALID_INDEX: error_string = "INVALID_INDEX"; break;
#endif
        }
        std::cout << "[OpenGL Error] ("
            << error
            << ": "
            << error_string
            << ")\n";
        count++;
    }
    return count > 0;
}

/**
 * Clear the current frame buffer with the current clear color
 * @param mask
 */
inline void clear_buffer(bitfield mask = OMEGA_GL_COLOR_BUFFER_BIT) {
    glClear(mask);
}

/**
 * Set the clear color with normalized rgba params
 */
inline void set_clear_color(f32 r, f32 g, f32 b, f32 a) {
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
 * @param sfactor (default = OMEGA_GL_SRC_ALPHA)
 * @param dfactor (default = OMEGA_GL_ONE_MINUS_SRC_ALPHA)
 */
inline void enable_blending(macro sfactor = OMEGA_GL_SRC_ALPHA,
                            macro dfactor = OMEGA_GL_ONE_MINUS_SRC_ALPHA) {
    glEnable(OMEGA_GL_BLEND);
    glBlendFunc(sfactor, dfactor);
}

/**
 * Calls glDrawArrays
 * @param render_type
 * @param start
 * @param count
 */
inline void draw_arrays(macro render_type, u32 start, u32 count) {
    glDrawArrays(render_type, start, count);
}

/**
 * Calss glDrawElements
 * @param mode render mode (i.e. OMEGA_GL_TRIANGLES)
 * @param count number of indices from index buffer
 * @param type type of indices (i.e. OMEGA_GL_UNSIGNED_INT)
 * @param indices pointer to the indices or if using IndexBuffer (nullptr)
 */
inline void draw_elements(macro mode,
                          i32 count,
                          u32 type,
                          const void *indices) {
    glDrawElements(mode, count, type, indices);
}

} // namespace omega::gfx

#endif // OMEGA_GFX_GL_HPP
