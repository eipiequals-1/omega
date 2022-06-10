#ifndef _LIBGL2D_EVENTS_INPUTPROCESSOR_H_
#define _LIBGL2D_EVENTS_INPUTPROCESSOR_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include "libGL2D/events/key_processor.h"
#include "libGL2D/physics/math.h"

namespace libgl {

using Event = SDL_Event;

/**
 * Describes possible events
 */
enum class EventType {
	kQuit = SDL_QUIT,
	kWindowEvent = SDL_WINDOWEVENT
};

/**
 * Represents the type of mouse
 */
enum class MouseButton {
	kMouseLeft = SDL_BUTTON_LEFT,
	KMouseRight = SDL_BUTTON_RIGHT
};

/**
 * Abstraction for all input from the user
 * Handles window, mouse, keyboard, etc events
 */
class InputProcessor {
   public:
	InputProcessor();

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

	KeyProcessor &GetKeyProcessor() { return key_processor_; }
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
	KeyProcessor key_processor_;
	glm::vec2 mouse_pos_;  // mouse_pos relative to bottom left
	uint32_t buttons_;
	uint32_t prev_buttons_;
};

}  // namespace libgl

#endif  // _LIBGL2D_EVENTS_INPUTPROCESSOR_H_