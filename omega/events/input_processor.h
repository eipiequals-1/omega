#ifndef OMEGA_EVENTS_INPUTPROCESSOR_H
#define OMEGA_EVENTS_INPUTPROCESSOR_H

#include <cstdint>

#include "omega/events/event.h"
#include "omega/events/input_manager.h"
#include "omega/util/util.h"

namespace omega::events {

class InputProcessor {
  public:
    InputProcessor();
    virtual ~InputProcessor();

    void listen();
    // mouse and key input
    virtual void on_key_down(Key key) = 0;
    virtual void on_key_up(Key key) = 0;
    virtual void on_mouse_down(u32 screen_x, u32 screen_y, MouseButton button) = 0;
    virtual void on_mouse_up(u32 screen_x, u32 screen_y, MouseButton button) = 0;
    // window input
    virtual void on_window_resized(u32 window_width, u32 window_height) = 0;
    virtual void on_window_closed() = 0;
};

} // namespace omega::events

#endif // OMEGA_EVENTS_INPUTPROCESSOR_H