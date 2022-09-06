#ifndef OMEGA_EVENTS_INPUTMANAGER_H
#define OMEGA_EVENTS_INPUTMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include "omega/core/application.h"
#include "omega/events/event.h"
#include "omega/events/key_manager.h"
#include "omega/util/util.h"

namespace omega::events {

using namespace omega::util;
using namespace omega::core;

/**
 * Abstraction for all input from the user
 * Handles window, mouse, keyboard, etc events
 */
class InputManager {
  public:
    InputManager(const InputManager &) = delete;
    InputManager operator=(const InputManager &) = delete;

    static sptr<InputManager> instance() {
        static sptr<InputManager> input = sptr<InputManager>(new InputManager());
        return input;
    }

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

    sptr<KeyManager> &get_key_manager() { return key_manager; }
    const glm::vec2 &get_mouse_pos() const { return mouse_pos; }
    glm::vec2 get_mouse_move() const { return relative_mode ? mouse_pos : mouse_pos - prev_mouse_pos; }

    void set_relative_mouse_mode(bool mode) {
        SDL_SetRelativeMouseMode(mode ? SDL_TRUE : SDL_FALSE);
        relative_mode = mode;
    }
    bool get_relative_mouse_mode() const { return relative_mode; }

    /**
     * Returns if the given button is pressed
     * @param button to test
     * @return if the button passes the test
     */
    bool mouse_button_down(MouseButton button) const {
        return (buttons & SDL_BUTTON((int)button)) == 1;
    }

    /**
     * Returns if the given button is not pressed
     * @param button to test
     * @return if the button passes the test
     */
    bool mouse_button_up(MouseButton button) const {
        return (buttons & SDL_BUTTON((int)button)) == 0;
    }

    /**
     * Returns if the given button has just been pressed on this frame
     * @param button to test
     * @return if the button passes the test
     */
    bool mouse_button_just_pressed(MouseButton button) const {
        return mouse_button_down(button) && (prev_buttons & SDL_BUTTON((int)button)) == 0;
    }

    /**
     * Returns if the given button has just been released on this frame
     * @param button to test
     * @return if the button passes the test
     */
    bool mouse_button_just_released(MouseButton button) const {
        return mouse_button_up(button) && (prev_buttons & SDL_BUTTON((int)button)) == 1;
    }

  private:
    InputManager();
    sptr<KeyManager> key_manager;
    glm::vec2 mouse_pos, prev_mouse_pos; // mouse_pos relative to bottom left
    u32 buttons;
    u32 prev_buttons;
    bool relative_mode;
};

} // namespace omega::events

#endif // OMEGA_EVENTS_INPUTMANAGER_H