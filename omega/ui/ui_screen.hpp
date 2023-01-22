#ifndef OMEGA_UI_UISCREEN_H
#define OMEGA_UI_UISCREEN_H

#include <vector>

#include "omega/events/input_processor.hpp"
#include "omega/ui/button/button.hpp"
#include "omega/util/math.hpp"

namespace omega::ui {

class UIScreen {
  public:
    UIScreen();
    virtual ~UIScreen();

    void update(const glm::vec2 &mouse_pos);
    void push_button(button::Button *button);
    void handle_buttons();

  protected:
    std::vector<button::Button *> buttons;
};

} // namespace omega::ui

#endif // OMEGA_UI_UISCREEN_H
