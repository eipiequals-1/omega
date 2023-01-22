#include "input_processor.hpp"

namespace omega::events {

using namespace omega::util;

InputProcessor::InputProcessor() {
}

InputProcessor::~InputProcessor() {
}

void InputProcessor::listen() {
    InputManager *input = InputManager::instance();
    Event event;
    while (input->poll_events(event)) {
        switch ((EventType)event.type) {
        case EventType::quit: {
            on_window_closed();
            break;
        }
        case EventType::window_event: {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                on_window_resized(event.window.data1, event.window.data2);
            }
            break;
        }
        case EventType::key_down: {
            on_key_down((Key)event.key.keysym.sym);
            break;
        }
        case EventType::key_up: {
            on_key_up((Key)event.key.keysym.sym);
            break;
        }
        case EventType::mouse_button_down: {
            MouseButton button;
            if (event.button.button == SDL_BUTTON_LEFT) {
                button = MouseButton::mouse_left;
            } else if (event.button.button == SDL_BUTTON_RIGHT) {
                button = MouseButton::mouse_right;
            } else {
                button = MouseButton::mouse_center;
            }
            on_mouse_down(input->get_mouse_pos().x, input->get_mouse_pos().y, button);
            break;
        }
        case EventType::mouse_button_up: {
            MouseButton button;
            if (event.button.button == SDL_BUTTON_LEFT) {
                button = MouseButton::mouse_left;
            } else if (event.button.button == SDL_BUTTON_RIGHT) {
                button = MouseButton::mouse_right;
            } else {
                button = MouseButton::mouse_center;
            }
            on_mouse_up(input->get_mouse_pos().x, input->get_mouse_pos().y, button);
            break;
        }
        default:
            break;
        }
    }
}

} // namespace omega
