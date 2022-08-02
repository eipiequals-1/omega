#include "window.h"

#include <iostream>

namespace omega {
Window::Window() : width_(0), height_(0), window_(nullptr), context_(nullptr) {
}

Window::~Window() {
	SDL_GL_DeleteContext(context_);
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
		Log("Failed to initialize SDL: '", SDL_GetError(), "'");
		return false;
	}
	// use the core OpenGL profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// specify version 4.5
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	// request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// force hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	WindowFlags window_flags = resizable ? WindowFlags::kOpenGLResizable : WindowFlags::kOpenGL;

	window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, (uint32_t)window_flags);
	if (window_ == nullptr) {
		Log("Failed to create window: '", SDL_GetError(), "'");
		SDL_Quit();
		return false;
	}

	context_ = SDL_GL_CreateContext(window_);
	if (context_ == nullptr) {
		Log("Failed to create GL Context: '", SDL_GetError(), "'");
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

}  // namespace omega
