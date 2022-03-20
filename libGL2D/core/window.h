#ifndef _LIBGL2D_CORE_WINDOW_H_
#define _LIBGL2D_CORE_WINDOW_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <cstdint>
#include <string>

#include "libGL2D/core/using.h"
#include "libGL2D/physics/math.h"

namespace libGL2D {

/**
 * Setup Config for Window
 */
class WinBuilder {
   public:
	WinBuilder() {
		width_ = 800;
		height_ = 450;
		window_title_ = "libGL2D - Window";
		win_flags_ = WindowFlags::kOpenGL;
		init_flags_ = InitFlags::kEverything;
	}

	uint32_t get_width() const { return width_; }
	uint32_t get_height() const { return height_; }
	const std::string &get_window_title() const { return window_title_; }
	WindowFlags get_win_flags() const { return win_flags_; }
	InitFlags get_init_flags() const { return init_flags_; }

	// config methods
	WinBuilder &width(uint32_t width) {
		width_ = width;
		return *this;
	}
	WinBuilder &height(uint32_t height) {
		height_ = height;
		return *this;
	}
	WinBuilder &window_title(const std::string &window_title) {
		window_title_ = window_title;
		return *this;
	}
	WinBuilder &win_flags(WindowFlags win_flags) {
		win_flags_ = win_flags;
		return *this;
	}
	WinBuilder &init_flags(InitFlags init_flags) {
		init_flags_ = init_flags;
		return *this;
	}

   private:
	uint32_t width_;
	uint32_t height_;
	std::string window_title_;
	WindowFlags win_flags_;
	InitFlags init_flags_;
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