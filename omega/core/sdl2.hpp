#ifndef OMEGA_CORE_SDL2_HPP
#define OMEGA_CORE_SDL2_HPP

#include <SDL3/SDL.h>

#include "omega/util/types.hpp"

namespace omega::core {

/**
 * Specifies how the Window should be set up.
 *
 * i.e. Fullscreen mode, Resizable, etc
 */
namespace WindowFlags {
enum : u32 {
    opengl = SDL_WINDOW_OPENGL,
    resizable = SDL_WINDOW_RESIZABLE,
    fullscreen = SDL_WINDOW_FULLSCREEN,
    none = 0
};
}

} // namespace omega::core

#endif // OMEGA_CORE_SDL2_HPP
