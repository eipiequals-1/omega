#include "ui_screen.hpp"

namespace omega::ui {

UIScreen::UIScreen() {}

UIScreen::~UIScreen() {
    for (auto &btn : buttons) {
        if (btn != nullptr)
            delete btn;
        btn = nullptr;
    }
}

void UIScreen::update(const glm::vec2 &mouse_pos) {
    for (auto &btn : buttons) {
        btn->set_hover(false);
        if (btn->contains_point(mouse_pos)) {
            btn->set_hover(true);
        }
    }
}

void UIScreen::push_button(button::Button *button) { buttons.push_back(button); }

void UIScreen::handle_buttons() {
    if (events::InputManager::instance()->mouse_button_just_released(
            events::MouseButton::mouse_left)) {
        for (auto &btn : buttons) {
            if (btn->get_hover()) {
                btn->on_click();
            }
        }
    }
}

} // namespace omega::ui
