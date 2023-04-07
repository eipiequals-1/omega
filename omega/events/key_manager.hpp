#ifndef OMEGA_EVENT_KEYMANAGER_HPP
#define OMEGA_EVENT_KEYMANAGER_HPP

#include <SDL2/SDL.h>

#include "omega/events/event.hpp"

namespace omega::events {

/**
 * KeyManager handles all keyboard input
 */
class KeyManager {
  public:
    KeyManager();
    /**
     * Must be called before InputProcessor::poll_events()
     */
    void prepare_for_update();
    /**
     * Must be called after InputProcessor::poll_events()
     */
    void update();

    /**
     * Returns if the given key was just pressed on the current frame
     * @param keycode the key to test
     * @return if the key passes the test
     */
    bool key_just_pressed(Key keycode) const;

    /**
     * Returns if the given key has been pressed for this frame and the last
     * @param keycode the key to test
     * @return if the key passes the test
     */
    bool key_held(Key keycode) const;

    /**
     * Returns if the given key was just released on the current frame
     * @param keycode the key to test
     * @return if the key passes the test
     */
    bool key_just_released(Key keycode) const;

    /**
     * Returns if the given key has not been pressed on the last 2 frames
     * @param keycode the key to test
     * @return if the key passes the test
     */
    bool key_never_pressed(Key keycode) const;

    /**
     * Returns if the given key is currently pressed
     * @param keycode the key to test
     * @return if the key passes the test
     */
    bool key_pressed(Key keycode) const;

  private:
    // copy of the key state for the last frame
    uint8_t keys_last_frame[SDL_NUM_SCANCODES];
    // where SDL stores the keys
    const uint8_t *keys_current_frame;
};

} // namespace omega::events

#endif // OMEGA_EVENT_KEYMANAGER_HPP
