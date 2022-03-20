#ifndef _LIBGL2D_EVENT_KEYPROCESSOR_H_
#define _LIBGL2D_EVENT_KEYPROCESSOR_H_

#include <SDL2/SDL.h>

namespace libGL2D {

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

class KeyProcessor {
   public:
	KeyProcessor();
	/**
	 * Must be called before SDL_PollEvents
	 */
	void PrepareForUpdate();
	/**
	 * Must be called after SDL_PollEvents
	 */
	void Update();

	// get key state
	bool KeyJustPressed(Key keycode) const;
	bool KeyHeld(Key keycode) const;
	bool KeyJustReleased(Key keycode) const;
	bool KeyNeverPressed(Key keycode) const;

	bool KeyPressed(Key keycode) const;

   private:
	uint8_t keys_last_frame_[SDL_NUM_SCANCODES];
	const uint8_t *keys_current_frame_;
};

}  // namespace libGL2D

#endif  // _LIBGL2D_EVENT_KEYPROCESSOR_H_