#ifndef _LIBGL2D_EVENT_KEYPROCESSOR_H_
#define _LIBGL2D_EVENT_KEYPROCESSOR_H_

#include <SDL2/SDL.h>

namespace libgl {

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

/**
 * KeyProcessor handles all keyboard input
 */
class KeyProcessor {
   public:
	KeyProcessor();
	/**
	 * Must be called before InputProcessor::PollEvents()
	 */
	void PrepareForUpdate();
	/**
	 * Must be called after InputProcessor::PollEvents()
	 */
	void Update();

	/**
	 * Returns if the given key was just pressed on the current frame
	 * @param keycode the key to test
	 * @return if the key passes the test
	 */
	bool KeyJustPressed(Key keycode) const;

	/**
	 * Returns if the given key has been pressed for this frame and the last
	 * @param keycode the key to test
	 * @return if the key passes the test
	 */
	bool KeyHeld(Key keycode) const;

	/**
	 * Returns if the given key was just released on the current frame
	 * @param keycode the key to test
	 * @return if the key passes the test
	 */
	bool KeyJustReleased(Key keycode) const;

	/**
	 * Returns if the given key has not been pressed on the last 2 frames
	 * @param keycode the key to test
	 * @return if the key passes the test
	 */
	bool KeyNeverPressed(Key keycode) const;

	/**
	 * Returns if the given key is currently pressed
	 * @param keycode the key to test
	 * @return if the key passes the test
	 */
	bool KeyPressed(Key keycode) const;

   private:
	uint8_t keys_last_frame_[SDL_NUM_SCANCODES];  // copy of the key state for the last frame
	const uint8_t *keys_current_frame_;           // where SDL stores the keys
};

}  // namespace libgl

#endif  // _LIBGL2D_EVENT_KEYPROCESSOR_H_