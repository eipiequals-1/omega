#ifndef _LIBGL2D_EVENT_KEYPROCESSOR_H_
#define _LIBGL2D_EVENT_KEYPROCESSOR_H_

#include <SDL2/SDL.h>

namespace libGL2D {

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
	bool KeyJustPressed(int keycode) const;
	bool KeyHeld(int keycode) const;
	bool KeyJustReleased(int keycode) const;
	bool KeyNeverPressed(int keycode) const;

	bool KeyPressed(int keycode) const;

   private:
	uint8_t keys_last_frame_[SDL_NUM_SCANCODES];
	const uint8_t *keys_current_frame_;
};

}  // namespace libGL2D

#endif  // _LIBGL2D_EVENT_KEYPROCESSOR_H_