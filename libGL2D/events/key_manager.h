#ifndef LIBGL2D_EVENT_KEYMANAGER_H
#define LIBGL2D_EVENT_KEYMANAGER_H

#include <SDL2/SDL.h>

#include "libGL2D/events/event.h"

namespace libgl {

/**
 * KeyManager handles all keyboard input
 */
class KeyManager {
   public:
	KeyManager();
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

#endif  // LIBGL2D_EVENT_KEYMANAGER_H