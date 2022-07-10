#include "input_manager.h"

namespace omega {

InputManager::InputManager() {
	key_manager_ = CreateSptr<KeyManager>();
}

void InputManager::PrepareForUpdate() {
	key_manager_->PrepareForUpdate();
}

bool InputManager::PollEvents(Event &event) {
	return SDL_PollEvent(&event);
}

void InputManager::Update() {
	key_manager_->Update();
	int x, y;
	prev_buttons_ = buttons_;
	buttons_ = SDL_GetMouseState(&x, &y);
	mouse_pos_.x = x;
	mouse_pos_.y = y;
}

}  // namespace omega