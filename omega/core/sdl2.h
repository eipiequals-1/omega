#ifndef OMEGA_CORE_USING_H
#define OMEGA_CORE_USING_H

#include <SDL2/SDL.h>

namespace omega::core {

/**
 * Specifies how the Window should be set up.
 *
 * i.e. Fullscreen mode, Resizable, etc
 */
enum class WindowFlags {
    k_opengl = SDL_WINDOW_OPENGL,
    k_opengl_resizable = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE,
    k_opengl_resizable_fullscreen = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN,
    k_none = 0
};

/**
 * Specifies how the SDL window, events, audio, etc should be set up
 */
enum class InitFlags {
    k_timer = SDL_INIT_TIMER,
    k_audio = SDL_INIT_AUDIO,
    k_video = SDL_INIT_VIDEO,
    k_joystick = SDL_INIT_JOYSTICK,
    k_events = SDL_INIT_EVENTS,
    k_everything = SDL_INIT_EVERYTHING
};

enum class WindowEvents {
    k_window_resized = SDL_WINDOWEVENT_RESIZED
};

} // namespace omega::core

#endif // OMEGA_CORE_USING_H