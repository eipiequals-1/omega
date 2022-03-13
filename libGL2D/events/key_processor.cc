#include "key_processor.h"

#include <SDL2/SDL.h>

#include <iostream>

namespace libGL2D {

KeyProcessor::KeyProcessor() : keys_current_frame_(nullptr) {
	keys_current_frame_ = SDL_GetKeyboardState(nullptr);
	// clear previous state memory
	memset(keys_last_frame_, 0, SDL_NUM_SCANCODES);  // 0 is temp memory address
}

void KeyProcessor::PrepareForUpdate() {
	// copy current frame to last frame
	memcpy(keys_last_frame_, keys_current_frame_, SDL_NUM_SCANCODES);
}

void KeyProcessor::Update() {
	keys_current_frame_ = SDL_GetKeyboardState(nullptr);  // get current state of keyboard
}

bool KeyProcessor::KeyJustPressed(int keycode) const {
	// if not pressed last frame and pressed now
	return !keys_last_frame_[keycode] && keys_current_frame_[keycode];
}

bool KeyProcessor::KeyHeld(int keycode) const {
	// if pressed last frame and now
	return keys_last_frame_[keycode] && keys_current_frame_[keycode];
}

bool KeyProcessor::KeyJustReleased(int keycode) const {
	// if pressed last frame and not now
	return keys_last_frame_[keycode] && !keys_current_frame_[keycode];
}

bool KeyProcessor::KeyNeverPressed(int keycode) const {
	// if not pressed last frame or this frame
	return !keys_last_frame_[keycode] && keys_current_frame_[keycode];
}

bool KeyProcessor::KeyPressed(int keycode) const {
	return keys_current_frame_[keycode];
}

}  // namespace libGL2D