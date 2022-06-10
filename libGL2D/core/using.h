#ifndef _LIBGL2D_CORE_USING_H_
#define _LIBGL2D_CORE_USING_H_

#include <SDL2/SDL.h>

#include <cstdarg>
#include <iostream>
#include <memory>

namespace libgl {

// a STL unique pointer
template <typename T>
using Uptr = std::unique_ptr<T>;

// a STL shared pointer
template <typename T>
using Sptr = std::shared_ptr<T>;

/**
 * Specifies how the Window should be set up.
 *
 * i.e. Fullscreen mode, Resizable, etc
 */
enum class WindowFlags {
	kOpenGL = SDL_WINDOW_OPENGL,
	kFullscreen = SDL_WINDOW_FULLSCREEN,
	kShown = SDL_WINDOW_SHOWN,
	kHidden = SDL_WINDOW_HIDDEN,
	kResizable = SDL_WINDOW_RESIZABLE,
	kOpenGLResizable = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE,
	kOpenGLResizableFullscreen = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | kFullscreen,
	kNone = 0
};

/**
 * Specifies how the SDL window, events, audio, etc should be set up
 */
enum class InitFlags {
	kTimer = SDL_INIT_TIMER,
	kAudio = SDL_INIT_AUDIO,
	kVideo = SDL_INIT_VIDEO,
	kJoyStick = SDL_INIT_JOYSTICK,
	kEvents = SDL_INIT_EVENTS,
	kEverything = SDL_INIT_EVERYTHING
};

inline void Log() {
	std::cout << '\n';
}

/**
 * The official libgl logging function for proper formatting and ease of use
 * @param args any arguments to print
 */
template <typename T, typename... Args>
void Log(T t, Args... args) {
	std::cout << t << ' ';
	Log(args...);
}

}  // namespace libgl

#endif  // _LIBGL2D_CORE_USING_H_