#ifndef _LIBGL2D_CORE_WINDOW_H_
#define _LIBGL2D_CORE_WINDOW_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <cstdint>
#include <string>

#include "libGL2D/physics/math.h"

namespace libGL2D {

struct WinBuilder {
	uint32_t width;
	uint32_t height;
	const std::string &window_title;
	uint32_t win_flags;
	uint32_t init_flags;
};

class Window {
   public:
	Window();
	virtual ~Window();

	virtual bool Init(const WinBuilder &builder);

	virtual void set_clear_color(const glm::vec4 &color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}
	virtual void Clear(GLbitfield mask = GL_COLOR_BUFFER_BIT);
	virtual void SwapBuffers();

   protected:
	uint32_t width_;
	uint32_t height_;
	SDL_Window *window_;
};

}  // namespace libGL2D

#endif  // _LIBGL2D_CORE_WINDOW_H_