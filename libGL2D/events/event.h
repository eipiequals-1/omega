#ifndef LIBGL2D_EVENTS_EVENT_H
#define LIBGL2D_EVENTS_EVENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

namespace libgl {

using Event = SDL_Event;

/**
 * Describes possible events
 */
enum class EventType {
	kQuit = SDL_QUIT,
	kWindowEvent = SDL_WINDOWEVENT,
	kKeyDown = SDL_KEYDOWN,
	kKeyUp = SDL_KEYUP,
	kMouseButtonDown = SDL_MOUSEBUTTONDOWN,
	kMouseButtonUp = SDL_MOUSEBUTTONUP
};

/**
 * Represents the type of mouse
 */
enum class MouseButton {
	kMouseLeft = SDL_BUTTON_LEFT,
	kMouseRight = SDL_BUTTON_RIGHT,
	kMouseCenter = SDL_BUTTON_MIDDLE
};

/**
 * Represents all the Keys
 */
enum class Key {
	kEscape = SDL_SCANCODE_ESCAPE,
	kEnter = SDL_SCANCODE_RETURN,
	kSpace = SDL_SCANCODE_SPACE,
	kBackspace = SDL_SCANCODE_BACKSPACE,
	kTab = SDL_SCANCODE_TAB,
	kLeft = SDL_SCANCODE_LEFT,
	kRight = SDL_SCANCODE_RIGHT,
	kUp = SDL_SCANCODE_UP,
	kDown = SDL_SCANCODE_DOWN,

	k0 = SDL_SCANCODE_0,
	k1 = SDL_SCANCODE_1,
	k2 = SDL_SCANCODE_2,
	k3 = SDL_SCANCODE_3,
	k4 = SDL_SCANCODE_4,
	k5 = SDL_SCANCODE_5,
	k6 = SDL_SCANCODE_6,
	k7 = SDL_SCANCODE_7,
	k8 = SDL_SCANCODE_8,
	k9 = SDL_SCANCODE_9,

	kA = SDL_SCANCODE_A,
	kB = SDL_SCANCODE_B,
	kC = SDL_SCANCODE_C,
	kD = SDL_SCANCODE_D,
	kE = SDL_SCANCODE_E,
	kF = SDL_SCANCODE_F,
	kG = SDL_SCANCODE_G,
	kH = SDL_SCANCODE_H,
	kI = SDL_SCANCODE_I,
	kJ = SDL_SCANCODE_J,
	kK = SDL_SCANCODE_K,
	kL = SDL_SCANCODE_L,
	kM = SDL_SCANCODE_M,
	kN = SDL_SCANCODE_N,
	kO = SDL_SCANCODE_O,
	kP = SDL_SCANCODE_P,
	kQ = SDL_SCANCODE_Q,
	kR = SDL_SCANCODE_R,
	kS = SDL_SCANCODE_S,
	kT = SDL_SCANCODE_T,
	kU = SDL_SCANCODE_U,
	kV = SDL_SCANCODE_V,
	kW = SDL_SCANCODE_W,
	kX = SDL_SCANCODE_X,
	kY = SDL_SCANCODE_Y,
	kZ = SDL_SCANCODE_Z
};

}  // namespace libgl

#endif  // LIBGL2D_EVENTS_EVENT_H