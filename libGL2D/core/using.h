#ifndef _LIBGL2D_CORE_USING_H_
#define _LIBGL2D_CORE_USING_H_

#include <SDL2/SDL.h>

#include <memory>

namespace libgl {

template <typename T>
using Uptr = std::unique_ptr<T>;

template <typename T>
using Sptr = std::shared_ptr<T>;

enum class WindowFlags {
	kOpenGL = SDL_WINDOW_OPENGL,
	kFullscreen = SDL_WINDOW_FULLSCREEN,
	kShown = SDL_WINDOW_SHOWN,
	kHidden = SDL_WINDOW_HIDDEN,
	kNone = 0
};

enum class InitFlags {
	kTimer = SDL_INIT_TIMER,
	kAudio = SDL_INIT_AUDIO,
	kVideo = SDL_INIT_VIDEO,
	kJoyStick = SDL_INIT_JOYSTICK,
	kEvents = SDL_INIT_EVENTS,
	kEverything = SDL_INIT_EVERYTHING
};

}  // namespace libgl

#endif  // _LIBGL2D_CORE_USING_H_