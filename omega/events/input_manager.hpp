#ifndef OMEGA_EVENTS_INPUTMANAGER_HPP
#define OMEGA_EVENTS_INPUTMANAGER_HPP

#include <cstdint>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include "omega/events/event.hpp"
#include "omega/events/key_manager.hpp"
#include "omega/math/math.hpp"
#include "omega/util/std.hpp"
#include "omega/util/types.hpp"

namespace omega::core {class App;} // namespace omega::core

namespace omega::events {

/**
 * Abstraction for all input from the user
 * Handles window, mouse, keyboard, etc events
 */
class InputManager {
  public:
    InputManager();
    
    /**
     * Prepares data for updating.
     * IMPORTANT: must be called before PollEvents
     */
    void prepare_for_update();

    /**
     * Gets all events from window management system
     *
     * @param event struct to store event data
     * @return if there are still events
     */
    bool poll_events(Event &event);

    /**
     * Sets all the data about events to be used later
     * such as mouse position, keyboard events, etc
     */
    void update();

    KeyManager& get_key_manager() { return key_manager; }
    const math::vec2 &get_mouse_pos() const { return mouse_pos; }
    math::vec2 get_mouse_move() const {
        return relative_mode ? mouse_pos : mouse_pos - prev_mouse_pos;
    }

    /**
     * Set mouse relative mode for first person feel (true),
     * or third person feel (false)
     * @param mode
     */
    void set_relative_mouse_mode(bool mode) {
        SDL_SetRelativeMouseMode(mode ? SDL_TRUE : SDL_FALSE);
        relative_mode = mode;
    }
    /**
     * @return the current mode
     */
    bool get_relative_mouse_mode() const { return relative_mode; }

    /**
     * Returns if the given button is pressed
     * @param button to test
     * @return if the button passes the test
     */
    bool mouse_button_down(MouseButton button) const {
        return (SDL_BUTTON((i32)button) & buttons) != 0;
    }

    /**
     * Returns if the given button is not pressed
     * @param button to test
     * @return if the button passes the test
     */
    bool mouse_button_up(MouseButton button) const {
        return (SDL_BUTTON((i32)button) & buttons) == 0;
    }

    /**
     * Returns if the given button has just been pressed on this frame
     * @param button to test
     * @return if the button passes the test
     */
    bool mouse_button_just_pressed(MouseButton button) const {
        return mouse_button_down(button) &&
            ((SDL_BUTTON((i32)button) & prev_buttons) == 0);
    }

    /**
     * Returns if the given button has just been released on this frame
     * @param button to test
     * @return if the button passes the test
     */
    bool mouse_button_just_released(MouseButton button) const {
        return mouse_button_up(button) &&
            ((SDL_BUTTON((i32)button) & prev_buttons) != 0);
    }

    const math::vec2 &get_scroll_wheel() const {
        return scroll_wheel;
    }

  private:
    friend class omega::core::App;

    // keys
    KeyManager key_manager;
    math::vec2 mouse_pos{0.0f}, prev_mouse_pos{0.0f};
    math::vec2 scroll_wheel{0.0f}; // mouse_pos relative to bottom left

    // mouse
    u32 buttons = 0;
    u32 prev_buttons = 0;
    bool relative_mode = false;
};

} // namespace omega::events

#endif // OMEGA_EVENTS_INPUTMANAGER_HPP
