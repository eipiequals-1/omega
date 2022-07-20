#ifndef OMEGA_CORE_USING_H
#define OMEGA_CORE_USING_H

#include <SDL2/SDL.h>

#include <cstdarg>
#include <iostream>
#include <memory>

namespace omega {

// a STL unique pointer
template <typename T>
using Uptr = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr Uptr<T> CreateUptr(Args&&... args) {
	return std::make_unique<T>(std::forward<Args>(args)...);
}

// a STL shared pointer
template <typename T>
using Sptr = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr Sptr<T> CreateSptr(Args&&... args) {
	return std::make_shared<T>(std::forward<Args>(args)...);
}

/**
 * Specifies how the Window should be set up.
 *
 * i.e. Fullscreen mode, Resizable, etc
 */
enum class WindowFlags {
	kOpenGL = SDL_WINDOW_OPENGL,
	kOpenGLResizable = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE,
	kOpenGLResizableFullscreen = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN,
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

enum class WindowEvents {
	kWindowResized = SDL_WINDOWEVENT_RESIZED
};

inline void Log() {
	std::cout << '\n';
}

/**
 * The official omega logging function for proper formatting and ease of use
 * @param args any arguments to print
 */
template <typename T, typename... Args>
void Log(T t, Args... args) {
	std::cout << t << ' ';
	Log(args...);
}

}  // namespace omega

#endif  // OMEGA_CORE_USING_H