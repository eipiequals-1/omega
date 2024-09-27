#include "input_manager.hpp"

#include "omega/core/window.hpp"

namespace omega::events {

void InputManager::prepare_for_update() {
    key_manager.prepare_for_update();
    // reset scroll wheel status
    mouse.scroll_wheel = math::vec2(0.0f);
}

bool InputManager::poll_events(Event &event) {
    return SDL_PollEvent(&event);
}

void InputManager::update() {
    key_manager.update();
    // get the mouse state and store the previous frame's state
    int x, y;
    mouse.prev_buttons = mouse.buttons;
    mouse.last_pos = mouse.pos;
    if (mouse.relative_mode) {
        mouse.buttons = SDL_GetRelativeMouseState(&x, &y);
        mouse.pos.x = (f32)x;
        mouse.pos.y = -(f32)y;
    } else {
        mouse.buttons = SDL_GetMouseState(&x, &y);
        mouse.pos.x = (f32)x;
        mouse.pos.y = (f32)(core::Window::instance()->get_height() - y);
    }
}

} // namespace omega::events
