#include "button.h"

namespace omega::ui::button {

Button::Button(float x, float y, float w, float h, std::function<void()> on_click) : on_click_listener(on_click) {
    hover = false;
    rect = glm::rectf(x, y, w, h);
}

Button::~Button() {
}

} // namespace omega::ui::button
