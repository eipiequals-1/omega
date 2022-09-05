#include "input_manager.h"

namespace omega {

InputManager::InputManager() : mouse_pos_(0.0f), prev_mouse_pos_(0.0f) {
	key_manager_ = create_sptr<KeyManager>();
	relative_mode_ = false;
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
	prev_mouse_pos_ = mouse_pos_;
	if (relative_mode_) {
		buttons_ = SDL_GetRelativeMouseState(&x, &y);
		mouse_pos_.x = (float)x;
		mouse_pos_.y = -(float)y;
	} else {
		buttons_ = SDL_GetMouseState(&x, &y);
		mouse_pos_.x = (float)x;
		mouse_pos_.y = (float)(Application::Instance().GetWindow()->GetHeight() - y);
	}
}

}  // namespace omega