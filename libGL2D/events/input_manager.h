#ifndef LIBGL2D_EVENTS_INPUTMANAGER_H
#define LIBGL2D_EVENTS_INPUTMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include "libGL2D/core/using.h"
#include "libGL2D/events/event.h"
#include "libGL2D/events/key_manager.h"
#include "libGL2D/physics/math.h"

namespace libgl {

/**
 * Abstraction for all input from the user
 * Handles window, mouse, keyboard, etc events
 */
class InputManager {
   public:
	InputManager(const InputManager &) = delete;
	InputManager operator=(const InputManager &) = delete;

	static InputManager &Instance() {
		static InputManager input;
		return input;
	}

	/**
	 * Prepares data for updating.
	 * IMPORTANT: must be called before PollEvents
	 */
	void PrepareForUpdate();

	/**
	 * Gets all events from window management system
	 *
	 * @param event struct to store event data
	 * @return if there are still events
	 */
	bool PollEvents(Event &event);

	/**
	 * Sets all the data about events to be used later
	 * such as mouse position, keyboard events, etc
	 */
	void Update();

	Sptr<KeyManager> &GetKeyManager() { return key_manager_; }
	const glm::vec2 &GetMousePos() const { return mouse_pos_; }

	/**
	 * Returns if the given button is pressed
	 * @param button to test
	 * @return if the button passes the test
	 */
	bool MouseButtonDown(MouseButton button) const {
		return (buttons_ & SDL_BUTTON((int)button)) == 1;
	}

	/**
	 * Returns if the given button is not pressed
	 * @param button to test
	 * @return if the button passes the test
	 */
	bool MouseButtonUp(MouseButton button) const {
		return (buttons_ & SDL_BUTTON((int)button)) == 0;
	}

	/**
	 * Returns if the given button has just been pressed on this frame
	 * @param button to test
	 * @return if the button passes the test
	 */
	bool MouseButtonJustPressed(MouseButton button) const {
		return MouseButtonDown(button) && (prev_buttons_ & SDL_BUTTON((int)button)) == 0;
	}

	/**
	 * Returns if the given button has just been released on this frame
	 * @param button to test
	 * @return if the button passes the test
	 */
	bool MouseButtonJustReleased(MouseButton button) const {
		return MouseButtonUp(button) && (prev_buttons_ & SDL_BUTTON((int)button)) == 1;
	}

   private:
	InputManager();
	Sptr<KeyManager> key_manager_;
	glm::vec2 mouse_pos_;  // mouse_pos relative to bottom left
	uint32_t buttons_;
	uint32_t prev_buttons_;
};

}  // namespace libgl

#endif  // LIBGL2D_EVENTS_INPUTMANAGER_H