#include "input_manager.h"

namespace omega::events {

InputManager::InputManager() : mouse_pos(0.0f), prev_mouse_pos(0.0f) {
    key_manager = create_sptr<KeyManager>();
    relative_mode = false;
}

void InputManager::prepare_for_update() {
    key_manager->prepare_for_update();
}

bool InputManager::poll_events(Event &event) {
    return SDL_PollEvent(&event);
}

void InputManager::update() {
    key_manager->update();
    // get the mouse state and store the previous frame's state
    int x, y;
    prev_buttons = buttons;
    prev_mouse_pos = mouse_pos;
    if (relative_mode) {
        buttons = SDL_GetRelativeMouseState(&x, &y);
        mouse_pos.x = (f32)x;
        mouse_pos.y = -(f32)y;
    } else {
        buttons = SDL_GetMouseState(&x, &y);
        mouse_pos.x = (f32)x;
        mouse_pos.y = (f32)(Window::instance()->get_height() - y);
    }
}

} // namespace omega::events