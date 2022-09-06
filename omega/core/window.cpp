#include "window.h"

#include <iostream>

#include "omega/core/sdl2.h"

namespace omega::core {

Window::Window() : width(0), height(0), window(nullptr), context(nullptr) {
}

Window::~Window() {
    SDL_GL_DeleteContext(context);
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    window = nullptr;
    SDL_Quit();
}

bool Window::init(u32 width, u32 height, bool resizable, const std::string &title) {
    this->width = width;
    this->height = height;
    if (SDL_Init((u32)InitFlags::k_everything) != 0) {
        util::log("Failed to initialize SDL: '", SDL_GetError(), "'");
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

    WindowFlags window_flags = resizable ? WindowFlags::k_opengl_resizable : WindowFlags::k_opengl;

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, (u32)window_flags);
    if (window == nullptr) {
        util::log("Failed to create window: '", SDL_GetError(), "'");
        SDL_Quit();
        return false;
    }

    context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        util::log("Failed to create GL Context: '", SDL_GetError(), "'");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    return true;
}

void Window::clear(GLbitfield mask) {
    glClear(mask);
}

void Window::swap_buffers() {
    SDL_GL_SwapWindow(window);
}

void Window::on_resize(u32 new_width, u32 new_height) {
    width = new_width;
    height = new_height;
}

} // namespace omega::core
