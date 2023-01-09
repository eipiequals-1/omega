#include "input_manager.h"

#include "omega/core/window.h"

namespace omega::events {

InputManager::InputManager() {
    key_manager = util::create_sptr<KeyManager>();
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
        mouse_pos.x = (float)x;
        mouse_pos.y = -(float)y;
    } else {
        buttons = SDL_GetMouseState(&x, &y);
        mouse_pos.x = (float)x;
        mouse_pos.y = (float)(core::Window::instance()->get_height() - y);
    }
}

} // namespace omega::events