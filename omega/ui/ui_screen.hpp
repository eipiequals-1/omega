#ifndef OMEGA_UI_UISCREEN_HPP
#define OMEGA_UI_UISCREEN_HPP

#include <vector>

#include "omega/ui/button/button.hpp"
#include "omega/util/math.hpp"
#include "omega/events/input_manager.hpp"

namespace omega::ui {

class UIScreen {
  public:
    UIScreen();
    virtual ~UIScreen();

    void update(const glm::vec2 &mouse_pos);
    void push_button(button::Button *button);
    void handle_buttons(events::InputManager &input);

  protected:
    std::vector<button::Button *> buttons;
};

} // namespace omega::ui

#endif // OMEGA_UI_UISCREEN_HPP
