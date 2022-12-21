#ifndef OMEGA_UI_BUTTON_BUTTON_H
#define OMEGA_UI_BUTTON_BUTTON_H

#include <functional>

#include "omega/gfx/sprite_batch.h"
#include "omega/scene/entity.h"
#include "omega/util/util.h"

namespace omega::ui::button {

using namespace omega::scene;

class Button : public RectComponent {
  public:
    Button(float x, float y, float w, float h, std::function<void()> on_click);
    virtual ~Button();

    virtual void render() = 0;
    void render(float dt) override {
        (void)dt;
        render();
    }

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
    std::function<void()> on_click_listener;
    bool hover;
};

} // namespace omega::ui::button

#endif // OMEGA_UI_BUTTON_BUTTON_H