#include "key_manager.h"

#include <SDL2/SDL.h>

#include <iostream>

namespace libgl {

KeyManager::KeyManager() : keys_current_frame_(nullptr) {
	keys_current_frame_ = SDL_GetKeyboardState(nullptr);
	// clear previous state memory
	memset(keys_last_frame_, 0, SDL_NUM_SCANCODES);  // 0 is temp memory address
}

void KeyManager::PrepareForUpdate() {
	// copy current frame to last frame
	memcpy(keys_last_frame_, keys_current_frame_, SDL_NUM_SCANCODES);
}

void KeyManager::Update() {
	keys_current_frame_ = SDL_GetKeyboardState(nullptr);  // get current state of keyboard
}

bool KeyManager::KeyJustPressed(Key keycode) const {
	// if not pressed last frame and pressed now
	return !keys_last_frame_[(int)keycode] && keys_current_frame_[(int)keycode];
}

bool KeyManager::KeyHeld(Key keycode) const {
	// if pressed last frame and now
	return keys_last_frame_[(int)keycode] && keys_current_frame_[(int)keycode];
}

bool KeyManager::KeyJustReleased(Key keycode) const {
	// if pressed last frame and not now
	return keys_last_frame_[(int)keycode] && !keys_current_frame_[(int)keycode];
}

bool KeyManager::KeyNeverPressed(Key keycode) const {
	// if not pressed last frame or this frame
	return !keys_last_frame_[(int)keycode] && keys_current_frame_[(int)keycode];
}

bool KeyManager::KeyPressed(Key keycode) const {
	return keys_current_frame_[(int)keycode];
}

}  // namespace libgl