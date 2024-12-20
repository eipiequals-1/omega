#ifndef OMEGA_EVENTS_MOUSE_HPP
#define OMEGA_EVENTS_MOUSE_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_mouse.h>

#include "omega/core/window.hpp"
#include "omega/events/event.hpp"
#include "omega/math/math.hpp"
#include "omega/util/types.hpp"

namespace omega::events {

struct Mouse {
    /**
     * Set mouse relative mode for first person feel (true),
     * or third person feel (false)
     * @param mode
     */
    void set_relative_mode(bool mode) {
        SDL_SetWindowRelativeMouseMode(
            core::Window::instance()->get_native_window(), mode);
        relative_mode = mode;
    }

    bool get_relative_mode() const {
        return relative_mode;
    }

    math::vec2 get_move() const {
        return relative_mode ? pos : pos - last_pos;
    }

    bool operator[](MouseButton button) const {
        return button_down(button);
    }

    /**
     * Returns if the given button is pressed
     * @param button to test
     * @return if the button passes the test
     */
    bool button_down(MouseButton button) const {
        return (SDL_BUTTON_MASK((i32)button) & buttons) != 0;
    }

    /**
     * Returns if the given button is not pressed
     * @param button to test
     * @return if the button passes the test
     */
    bool button_up(MouseButton button) const {
        return (SDL_BUTTON_MASK((i32)button) & buttons) == 0;
    }

    /**
     * Returns if the given button has just been pressed on this frame
     * @param button to test
     * @return if the button passes the test
     */
    bool button_just_pressed(MouseButton button) const {
        return button_down(button) &&
               ((SDL_BUTTON_MASK((i32)button) & prev_buttons) == 0);
    }

    /**
     * Returns if the given button has just been released on this frame
     * @param button to test
     * @return if the button passes the test
     */
    bool button_just_released(MouseButton button) const {
        return button_up(button) &&
               ((SDL_BUTTON_MASK((i32)button) & prev_buttons) != 0);
    }

    const math::vec2 &get_scroll_wheel() const {
        return scroll_wheel;
    }

    void set_sensitivity(f32 s) {
        sensitivity = s;
    }

    f32 get_sensitivity() const {
        return sensitivity;
    }

    u32 buttons = 0;
    u32 prev_buttons = 0;
    bool relative_mode = false;

    math::vec2 pos{0.0f}, last_pos{0.0f};
    math::vec2 scroll_wheel{0.0f}; // mouse_pos relative to bottom left
    f32 sensitivity = 0.1f;
};

} // namespace omega::events

#endif // OMEGA_EVENTS_MOUSE_HPP
