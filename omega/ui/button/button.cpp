#include "button.h"

namespace omega {

Button::Button(float x, float y, float w, float h, std::function<void()> on_click) : RectComponent(x, y, w, h), on_click_(on_click) {
	hover_ = false;
}

Button::~Button() {
}

}  // namespace omega
