#ifndef OMEGA_CORE_SDL2_HPP
#define OMEGA_CORE_SDL2_HPP

#include <SDL2/SDL.h>

namespace omega::core {

/**
 * Specifies how the Window should be set up.
 *
 * i.e. Fullscreen mode, Resizable, etc
 */
enum class WindowFlags {
    opengl = SDL_WINDOW_OPENGL,
    opengl_resizable = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE,
    opengl_resizable_fullscreen = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | 
    SDL_WINDOW_FULLSCREEN,
    none = 0
};

/**
 * Specifies how the SDL window, events, audio, etc should be set up
 */
enum class InitFlags {
    timer = SDL_INIT_TIMER,
    audio = SDL_INIT_AUDIO,
    video = SDL_INIT_VIDEO,
    joystick = SDL_INIT_JOYSTICK,
    events = SDL_INIT_EVENTS,
    everything = SDL_INIT_EVERYTHING
};

} // namespace omega::core

#endif // OMEGA_CORE_SDL2_HPP
