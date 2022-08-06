#ifndef OMEGA_CORE_WINDOW_H
#define OMEGA_CORE_WINDOW_H

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <cstdint>
#include <string>

#include "omega/core/using.h"
#include "omega/core/viewport.h"
#include "omega/physics/math.h"

namespace omega {

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
	virtual bool Init(uint32_t width, uint32_t height, bool resizable, const std::string &title);

	/**
	 * Specify the window clear color and abstracts it
	 * @param color of (r, g, b, a) components
	 */
	virtual void SetClearColor(const glm::vec4 &color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}
	virtual void Clear(GLbitfield mask = GL_COLOR_BUFFER_BIT);
	virtual void SwapBuffers();
	virtual void OnResize(uint32_t new_width, uint32_t new_height);

	uint32_t GetWidth() const { return width_; }
	uint32_t GetHeight() const { return height_; }
	SDL_Window *GetNativeWindow() { return window_; }
	SDL_GLContext GetGLContext() { return context_; }

   protected:
	uint32_t width_;
	uint32_t height_;
	SDL_Window *window_;
	SDL_GLContext context_;
};

}  // namespace omega

#endif  // OMEGA_CORE_WINDOW_H