#include "key_manager.hpp"

#include <SDL3/SDL.h>

#include <iostream>

namespace omega::events {

KeyManager::KeyManager() : keys_current_frame(nullptr) {
    keys_current_frame = SDL_GetKeyboardState(nullptr);
    // clear previous state memory
    memset(keys_last_frame, 0, SDL_SCANCODE_COUNT); // 0 is temp memory address
}

void KeyManager::prepare_for_update() {
    // copy current frame to last frame
    memcpy(keys_last_frame, keys_current_frame, SDL_SCANCODE_COUNT);
}

void KeyManager::update() {
    // get current state of keyboard
    keys_current_frame = SDL_GetKeyboardState(nullptr);
}

bool KeyManager::key_just_pressed(Key keycode) const {
    // if not pressed last frame and pressed now
    return !keys_last_frame[(i32)keycode] && keys_current_frame[(i32)keycode];
}

bool KeyManager::key_held(Key keycode) const {
    // if pressed last frame and now
    return keys_last_frame[(i32)keycode] && keys_current_frame[(i32)keycode];
}

bool KeyManager::key_just_released(Key keycode) const {
    // if pressed last frame and not now
    return keys_last_frame[(i32)keycode] && !keys_current_frame[(i32)keycode];
}

bool KeyManager::key_never_pressed(Key keycode) const {
    // if not pressed last frame or this frame
    return !keys_last_frame[(i32)keycode] && keys_current_frame[(i32)keycode];
}

bool KeyManager::key_pressed(Key keycode) const {
    return keys_current_frame[(i32)keycode];
}

} // namespace omega::events
