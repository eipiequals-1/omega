#include "button.h"

namespace omega::ui::button {

Button::Button(f32 x, f32 y, f32 w, f32 h, std::function<void()> on_click) : RectComponent(), on_click_listener(on_click) {
    hover = false;
    rect = glm::rectf(x, y, w, h);
}

Button::~Button() {
}

} // namespace omega::ui::button
