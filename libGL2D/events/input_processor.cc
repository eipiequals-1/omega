#include "input_processor.h"

namespace libGL2D {

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
	buttons_ = SDL_GetMouseState(&x, &y);
	mouse_pos_.x = x;
	mouse_pos_.y = y;
}

}  // namespace libGL2D