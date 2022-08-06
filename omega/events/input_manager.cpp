#include "input_manager.h"

namespace omega {

InputManager::InputManager() : mouse_pos_(0.0f), prev_mouse_pos_(0.0f) {
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
	// get the mouse state and store the previous frame's state
	int x, y;
	prev_buttons_ = buttons_;
	buttons_ = SDL_GetMouseState(&x, &y);
	prev_mouse_pos_ = mouse_pos_;
	mouse_pos_.x = x;
	mouse_pos_.y = Application::Instance().GetWindow()->GetHeight() - y;
}

}  // namespace omega