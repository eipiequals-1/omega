#include "input_processor.h"

namespace omega {

InputProcessor::InputProcessor() {
}

InputProcessor::~InputProcessor() {
}

void InputProcessor::Listen() {
	sptr<InputManager> input = InputManager::Instance();
	Event event;
	while (input->PollEvents(event)) {
		switch ((EventType)event.type) {
		case EventType::k_quit: {
			OnWindowClosed();
			break;
		}
		case EventType::k_window_event: {
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				OnWindowResize(event.window.data1, event.window.data2);
			}
			break;
		}
		case EventType::k_key_down: {
			OnKeyDown((Key)event.key.keysym.sym);
			break;
		}
		case EventType::k_key_up: {
			OnKeyUp((Key)event.key.keysym.sym);
			break;
		}
		case EventType::k_mouse_button_down: {
			MouseButton button;
			if (event.button.button == SDL_BUTTON_LEFT) {
				button = MouseButton::k_mouse_left;
			} else if (event.button.button == SDL_BUTTON_RIGHT) {
				button = MouseButton::k_mouse_right;
			} else {
				button = MouseButton::k_mouse_center;
			}
			OnMouseDown(input->GetMousePos().x, input->GetMousePos().y, button);
			break;
		}
		case EventType::k_mouse_button_up: {
			MouseButton button;
			if (event.button.button == SDL_BUTTON_LEFT) {
				button = MouseButton::k_mouse_left;
			} else if (event.button.button == SDL_BUTTON_RIGHT) {
				button = MouseButton::k_mouse_right;
			} else {
				button = MouseButton::k_mouse_center;
			}
			OnMouseDown(input->GetMousePos().x, input->GetMousePos().y, button);
			break;
		}
		default:
			break;
		}
	}
}

}  // namespace omega