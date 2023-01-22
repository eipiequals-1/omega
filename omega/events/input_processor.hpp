#ifndef OMEGA_EVENTS_INPUTPROCESSOR_H
#define OMEGA_EVENTS_INPUTPROCESSOR_H

#include <cstdint>

#include "omega/events/event.hpp"
#include "omega/events/input_manager.hpp"
#include "omega/util/util.hpp"

namespace omega::events {

class InputProcessor {
  public:
    InputProcessor();
    virtual ~InputProcessor();

    void listen();
    // mouse and key input
    virtual void on_key_down(Key key) = 0;
    virtual void on_key_up(Key key) = 0;
    virtual void on_mouse_down(uint32_t screen_x, uint32_t screen_y, MouseButton button) = 0;
    virtual void on_mouse_up(uint32_t screen_x, uint32_t screen_y, MouseButton button) = 0;
    // window input
    virtual void on_window_resized(uint32_t window_width, uint32_t window_height) = 0;
    virtual void on_window_closed() = 0;
};

} // namespace omega::events

#endif // OMEGA_EVENTS_INPUTPROCESSOR_H
