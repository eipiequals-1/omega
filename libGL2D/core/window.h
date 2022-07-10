#ifndef LIBGL2D_CORE_WINDOW_H
#define LIBGL2D_CORE_WINDOW_H

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <cstdint>
#include <string>

#include "libGL2D/core/using.h"
#include "libGL2D/core/viewport.h"
#include "libGL2D/physics/math.h"

namespace libgl {

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
	 * @param builder the WinBuilder Object
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

   protected:
	uint32_t width_;
	uint32_t height_;
	SDL_Window *window_;
};

}  // namespace libgl

#endif  // LIBGL2D_CORE_WINDOW_H