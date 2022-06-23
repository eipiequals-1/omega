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

bool Window::Init(const WinBuilder &builder) {
	width_ = builder.GetWidth();
	height_ = builder.GetHeight();
	if (SDL_Init((uint32_t)builder.GetInitFlags()) != 0) {
		libgl::Log("Failed to initialize SDL: '", SDL_GetError(), "'");
		return false;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	window_ = SDL_CreateWindow(builder.GetWindowTitle().c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, (uint32_t)builder.GetWinFlags());
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
}  // namespace libgl
