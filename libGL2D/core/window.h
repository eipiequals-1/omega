#ifndef _LIBGL2D_CORE_WINDOW_H_
#define _LIBGL2D_CORE_WINDOW_H_

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
 * Setup Config for Window using Builder design pattern
 * Set the width, height, window title, window flags, and library init flags
 */
class WinBuilder {
   public:
	WinBuilder() {
		width_ = 800;
		height_ = 450;
		window_title_ = "libGL2D - Window";
		win_flags_ = WindowFlags::kOpenGLResizable;
		init_flags_ = InitFlags::kEverything;
		viewport_type_ = ViewportType::kStretch;
	}

	uint32_t GetWidth() const { return width_; }
	uint32_t GetHeight() const { return height_; }
	const std::string &GetWindowTitle() const { return window_title_; }
	WindowFlags GetWinFlags() const { return win_flags_; }
	InitFlags GetInitFlags() const { return init_flags_; }
	ViewportType GetViewportType() const { return viewport_type_; }

	/**
	 * Set the width of the window
	 * @param width
	 */
	WinBuilder &width(uint32_t width) {
		width_ = width;
		return *this;
	}

	/**
	 * Set the height of the window
	 * @param height
	 */
	WinBuilder &height(uint32_t height) {
		height_ = height;
		return *this;
	}

	/**
	 * Set the window title of the window
	 * @param window_title
	 */
	WinBuilder &window_title(const std::string &window_title) {
		window_title_ = window_title;
		return *this;
	}

	/**
	 * Set the window flags of the window
	 * @param win_flags
	 */
	WinBuilder &win_flags(WindowFlags win_flags) {
		win_flags_ = win_flags;
		return *this;
	}

	/**
	 * Set the initialization flags of the library
	 * @param init_flags
	 */
	WinBuilder &init_flags(InitFlags init_flags) {
		init_flags_ = init_flags;
		return *this;
	}

	/**
	 * Set the window viewport type
	 * @param viewport_type
	 */
	WinBuilder &viewport_type(ViewportType viewport_type) {
		viewport_type_ = viewport_type;
		return *this;
	}

   private:
	uint32_t width_;
	uint32_t height_;
	std::string window_title_;
	WindowFlags win_flags_;
	InitFlags init_flags_;
	ViewportType viewport_type_;
};

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
	virtual bool Init(const WinBuilder &builder);

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

   protected:
	uint32_t width_;
	uint32_t height_;
	SDL_Window *window_;
	Uptr<Viewport> viewport_;
};

}  // namespace libgl

#endif  // _LIBGL2D_CORE_WINDOW_H_