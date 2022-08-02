#include "button.h"

namespace omega {

Button::Button(float x, float y, float w, float h, std::function<void()> on_click) : RectComponent(), on_click_(on_click) {
	hover_ = false;
	rect_ = glm::rectf(x, y, w, h);
}

Button::~Button() {
}

}  // namespace omega
