#ifndef OMEGA_EVENTS_INPUTMANAGER_HPP
#define OMEGA_EVENTS_INPUTMANAGER_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>

#include <cstdint>

#include "omega/events/event.hpp"
#include "omega/events/key_manager.hpp"
#include "omega/events/mouse.hpp"
#include "omega/math/math.hpp"
#include "omega/util/std.hpp"
#include "omega/util/types.hpp"

namespace omega::core {
class App;
} // namespace omega::core

namespace omega::events {

/**
 * Abstraction for all input from the user
 * Handles window, mouse, keyboard, etc events
 */
class InputManager {
  public:
    // keys
    KeyManager key_manager;

    // mouse
    Mouse mouse;

    InputManager() = default;

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

  private:
    friend class omega::core::App;
};

} // namespace omega::events

#endif // OMEGA_EVENTS_INPUTMANAGER_HPP
