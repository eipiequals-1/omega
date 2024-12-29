#include "window.hpp"

#include <iostream>

#include "omega/core/sdl2.hpp"
#include "omega/util/log.hpp"

namespace omega::core {

Window::~Window() {
    if (context != nullptr) {
        SDL_GL_DestroyContext(context);
    }
    context = nullptr;
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    window = nullptr;
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
    SDL_Quit();
    OMEGA_INFO("Successfully closed libraries.");

    OMEGA_INFO("Successfully quit application.");
}

bool Window::init(u32 width,
                  u32 height,
                  bool resizable,
                  const std::string &title) {
    this->width = width;
    this->height = height;
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS)) {
        OMEGA_ERROR("Failed to initialize SDL: '{}'", SDL_GetError());
        return false;
    }

#ifdef EMSCRIPTEN
    // use the ES OpenGL profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    // specify version 3.0
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OMEGA_GL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OMEGA_GL_MINOR_VERSION);

#else
    // use the core OpenGL profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    // specify version 4.5
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OMEGA_GL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OMEGA_GL_MINOR_VERSION);

#endif
    // request a color buffer with 8-bits per RGBA channel
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // force hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    auto window_flags = resizable
                            ? (WindowFlags::opengl | WindowFlags::resizable)
                            : WindowFlags::opengl;
    // INFO: or can use SDL_CreateWindowWithProperties to specify pos
    window = SDL_CreateWindow(title.c_str(), width, height, window_flags);
    if (window == nullptr) {
        OMEGA_ERROR("Failed to create window: '{}'", SDL_GetError());
        return false;
    }
    OMEGA_INFO("Window created successfully.");

    context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        OMEGA_ERROR("Failed to create GL Context: '{}'", SDL_GetError());
        return false;
    }
    OMEGA_INFO("OpenGL Context successfully created.");
    if (!SDL_GL_SetSwapInterval(0)) {
        OMEGA_ERROR("Failed to disable Vsync: '{}'", SDL_GetError());
        return false;
    }
    OMEGA_INFO("Disabled Vsync.");

#ifndef EMSCRIPTEN
    // initialize glad
    if (gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) == 0) {
        OMEGA_ERROR("Failed to initialize Glad");
        return false;
    }
#endif
    OMEGA_INFO("OpenGL API successfully loaded.");
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
