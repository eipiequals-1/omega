#ifndef OMEGA_UI_UISCREEN_H
#define OMEGA_UI_UISCREEN_H

#include <vector>

#include "omega/events/input_processor.h"
#include "omega/ui/button/button.h"
#include "omega/util/util.h"

namespace omega::ui {

using namespace omega::ui::button;
using namespace omega::events;

class UIScreen {
  public:
    UIScreen();
    virtual ~UIScreen();

    void update(const glm::vec2 &mouse_pos);
    void push_button(Button *button);
    void handle_buttons();

  protected:
    std::vector<Button *> buttons;
};

} // namespace omega::ui

#endif // OMEGA_UI_UISCREEN_H