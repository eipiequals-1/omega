#ifndef OMEGA_CORE_WINDOW_H
#define OMEGA_CORE_WINDOW_H

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <cstdint>
#include <string>

#include "omega/core/viewport.h"
#include "omega/util/util.h"

namespace omega::core {

/**
 * Window abstraction of SDL_Window, SDL_SwapBuffers and
 *
 * OpenGL window functions
 */
class Window {
  public:
    Window();
    virtual ~Window();

    /**
     * Constructs the Window object and returns if it was successful
     * @param width the initial width of the window
     * @param height the initial height of the window
     * @param resizable if it can be resized
     * @param title the window title
     */
    virtual bool init(u32 width, u32 height, bool resizable, const std::string &title);

    /**
     * Specify the window clear color and abstracts it
     * @param color of (r, g, b, a) components
     */
    virtual void set_clear_color(const glm::vec4 &color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }
    virtual void clear(GLbitfield mask = GL_COLOR_BUFFER_BIT);
    virtual void swap_buffers();
    virtual void on_resize(u32 new_width, u32 new_height);

    u32 get_width() const { return width; }
    u32 get_height() const { return height; }
    SDL_Window *get_native_window() { return window; }
    SDL_GLContext get_gl_context() { return context; }

  protected:
    u32 width;
    u32 height;
    SDL_Window *window;
    SDL_GLContext context;
};

} // namespace omega::core

#endif // OMEGA_CORE_WINDOW_H