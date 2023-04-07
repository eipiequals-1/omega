#ifndef OMEGA_UI_BUTTON_BUTTON_HPP
#define OMEGA_UI_BUTTON_BUTTON_HPP

#include <functional>

#include "omega/util/math.hpp"

namespace omega::ui::button {

class Button {
  public:
    Button(float x, float y, float w, float h,
           std::function<void()> on_click) : rect(x, y, w, h),
                                             on_click_listener(on_click) {}
    virtual ~Button() = default;

    virtual void render() = 0;

    bool contains_point(const glm::vec2 &p) const {
        return rect.point_in_rect(p);
    }
    bool get_hover() const { return hover; }
    void set_hover(bool hover) { this->hover = hover; }

    void on_click() {
        if (on_click_listener != nullptr) {
            on_click_listener();
        }
    }

  protected:
    glm::rectf rect;
    std::function<void()> on_click_listener = nullptr;
    bool hover = false;
};

} // namespace omega::ui::button

#endif // OMEGA_UI_BUTTON_BUTTON_HPP
