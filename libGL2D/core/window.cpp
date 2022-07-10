#include "window.h"

#include <iostream>

namespace libgl {
Window::Window() : width_(0), height_(0), window_(nullptr) {
}

Window::~Window() {
	if (window_ != nullptr) {
		SDL_DestroyWindow(window_);
	}
	window_ = nullptr;
	SDL_Quit();
}

bool Window::Init(uint32_t width, uint32_t height, bool resizable, const std::string &title) {
	width_ = width;
	height_ = height;
	if (SDL_Init((uint32_t)InitFlags::kEverything) != 0) {
		libgl::Log("Failed to initialize SDL: '", SDL_GetError(), "'");
		return false;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	WindowFlags window_flags = resizable ? WindowFlags::kOpenGLResizable : WindowFlags::kOpenGL;

	window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, (uint32_t)window_flags);
	if (window_ == nullptr) {
		libgl::Log("Failed to create window: '", SDL_GetError(), "'");
		SDL_Quit();
		return false;
	}

	SDL_GLContext gl_context = SDL_GL_CreateContext(window_);
	if (gl_context == nullptr) {
		libgl::Log("Failed to create GL Context: '", SDL_GetError(), "'");
		SDL_DestroyWindow(window_);
		SDL_Quit();
		return false;
	}
	return true;
}

void Window::Clear(GLbitfield mask) {
	glClear(mask);
}

void Window::SwapBuffers() {
	SDL_GL_SwapWindow(window_);
}

void Window::OnResize(uint32_t new_width, uint32_t new_height) {
	width_ = new_width;
	height_ = new_height;
}

}  // namespace libgl
