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

using namespace omega::util;

/**
 * Window abstraction of SDL_Window, SDL_SwapBuffers and
 *
 * OpenGL window functions
 */
class Window {
  public:
    Window(const Window &) = delete;
    Window operator=(const Window &) = delete;
    virtual ~Window();

    static sptr<Window> instance() {
        static sptr<Window> win = sptr<Window>(new Window());
        return win;
    }

    /**
     * Constructs the Window object and returns if it was successful
     * @param width the initial width of the window
     * @param height the initial height of the window
     * @param resizable if it can be resized
     * @param title the window title
     */
    virtual bool init(uint32_t width, uint32_t height, bool resizable, const std::string &title);

    /**
     * Specify the framebuffer clear color and abstracts it
     * @param color of (r, g, b, a) components
     */
    virtual void set_clear_color(const glm::vec4 &color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    /**
     * Clear the current framebuffer with glClearColor
     * @param mask the buffer types to clear (default=GL_COLOR_BUFFER_BIT)
     */
    virtual void clear(GLbitfield mask = GL_COLOR_BUFFER_BIT);
    virtual void swap_buffers();
    virtual void on_resize(uint32_t new_width, uint32_t new_height);

    uint32_t get_width() const { return width; }
    uint32_t get_height() const { return height; }
    SDL_Window *get_native_window() { return window; }
    SDL_GLContext get_gl_context() { return context; }

  protected:
    Window();

    uint32_t width;
    uint32_t height;
    SDL_Window *window;
    SDL_GLContext context;
};

} // namespace omega::core

#endif // OMEGA_CORE_WINDOW_H