#ifndef OMEGA_UI_UISCREEN_H
#define OMEGA_UI_UISCREEN_H

#include <vector>

#include "omega/events/input_processor.h"
#include "omega/ui/button/button.h"
#include "omega/util/math.h"

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