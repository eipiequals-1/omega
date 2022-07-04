#include "input_processor.h"

namespace libgl {

InputProcessor::InputProcessor() {
}

InputProcessor::~InputProcessor() {
}

void InputProcessor::Listen() {
	InputManager &input = InputManager::Instance();
	Event event;
	while (input.PollEvents(event)) {
		switch ((EventType)event.type) {
		case EventType::kQuit: {
			OnWindowClosed();
			break;
		}
		case EventType::kWindowEvent: {
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				OnWindowResize(event.window.data1, event.window.data2);
			}
			break;
		}
		case EventType::kKeyDown: {
			OnKeyDown((Key)event.key.keysym.sym);
			break;
		}
		case EventType::kKeyUp: {
			OnKeyUp((Key)event.key.keysym.sym);
			break;
		}
		case EventType::kMouseButtonDown: {
			MouseButton button;
			if (event.button.button == SDL_BUTTON_LEFT) {
				button = MouseButton::kMouseLeft;
			} else if (event.button.button == SDL_BUTTON_RIGHT) {
				button = MouseButton::kMouseRight;
			} else {
				button = MouseButton::kMouseCenter;
			}
			OnMouseDown(input.GetMousePos().x, input.GetMousePos().y, button);
			break;
		}
		case EventType::kMouseButtonUp: {
			MouseButton button;
			if (event.button.button == SDL_BUTTON_LEFT) {
				button = MouseButton::kMouseLeft;
			} else if (event.button.button == SDL_BUTTON_RIGHT) {
				button = MouseButton::kMouseRight;
			} else {
				button = MouseButton::kMouseCenter;
			}
			OnMouseDown(input.GetMousePos().x, input.GetMousePos().y, button);
			break;
		}
		default:
			break;
		}
	}
}

}  // namespace libgl