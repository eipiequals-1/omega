#include "input_processor.h"

namespace libgl {

InputProcessor::InputProcessor() {
}

void InputProcessor::PrepareForUpdate() {
	key_processor_.PrepareForUpdate();
}

bool InputProcessor::PollEvents(Event &event) {
	return SDL_PollEvent(&event);
}

void InputProcessor::Update() {
	key_processor_.Update();
	int x, y;
	prev_buttons_ = buttons_;
	buttons_ = SDL_GetMouseState(&x, &y);
	mouse_pos_.x = x;
	mouse_pos_.y = y;
}

}  // namespace libgl