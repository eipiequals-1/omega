#ifndef OMEGA_CORE_WINDOW_H
#define OMEGA_CORE_WINDOW_H

#include <SDL2/SDL.h>

#include <cstdint>
#include <string>

#include "omega/gfx/gl.hpp"
#include "omega/core/viewport.hpp"
#include "omega/util/std.hpp"

namespace omega::core {

/**
 * Window abstraction of SDL_Window, SDL_SwapBuffers, and OpenGL window functions
 */
class Window {
  public:
    Window(const Window &) = delete;
    Window operator=(const Window &) = delete;
    ~Window();

    /**
     * @return pointer to window instance
     */
    static Window* instance() {
        static util::uptr<Window> win = util::uptr<Window>(new Window());
        return win.get();
    }

    /**
     * Constructs the Window object and returns if it was successful
     * @param width the initial width of the window
     * @param height the initial height of the window
     * @param resizable if it can be resized
     * @param title the window title
     */
    bool init(uint32_t width, uint32_t height, bool resizable, const std::string &title);

    /**
     * Specify the framebuffer clear color and abstracts it
     * @param color of (r, g, b, a) components
     */
    void set_clear_color(const glm::vec4 &color) const {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    /**
     * Clear the current framebuffer with glClearColor
     * @param mask the buffer types to clear (default=GL_COLOR_BUFFER_BIT)
     */
    void clear(GLbitfield mask = GL_COLOR_BUFFER_BIT);
    /**
     * Update the window with OpenGL rendering
     * analagous to SDL_GL_SwapWindow
     */
    void swap_buffers();
    /**
     * When the window changes size
     */
    void on_resize(uint32_t new_width, uint32_t new_height);

    /**
     * @return width
     */
    uint32_t get_width() const { return width; }
    /**
     * @return height
     */
    uint32_t get_height() const { return height; }
    /**
     * @return native SDL_Window *
     */
    SDL_Window *get_native_window() { return window; }
    /**
     * @return SDL_GLContext
     */
    SDL_GLContext get_gl_context() { return context; }

  private:
    Window() = default;

    uint32_t width = 0;
    uint32_t height = 0;
    // sdl
    SDL_Window *window = nullptr;
    SDL_GLContext context = nullptr;
};

} // namespace omega::core

#endif // OMEGA_CORE_WINDOW_H
