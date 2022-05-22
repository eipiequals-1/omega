#ifndef _LIBGL2D_EVENTS_INPUTPROCESSOR_H_
#define _LIBGL2D_EVENTS_INPUTPROCESSOR_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include "libGL2D/events/key_processor.h"
#include "libGL2D/physics/math.h"

namespace libgl {

using Event = SDL_Event;

enum class EventType {
	kQuit = SDL_QUIT,
	kWindowEvent = SDL_WINDOWEVENT
};

enum class MouseButton {
	kMouseLeft = SDL_BUTTON_LEFT,
	KMouseRight = SDL_BUTTON_RIGHT
};

class InputProcessor {
   public:
	InputProcessor();
	void PrepareForUpdate();
	bool PollEvents(Event &event);
	void Update();

	KeyProcessor &GetKeyProcessor() { return key_processor_; }
	const glm::vec2 &GetMousePos() const { return mouse_pos_; }
	bool MouseButtonDown(MouseButton button) const {
		return (buttons_ & SDL_BUTTON((int)button)) == 1;
	}
	bool MouseButtonUp(MouseButton button) const {
		return (buttons_ & SDL_BUTTON((int)button)) == 0;
	}
	bool MouseButtonJustPressed(MouseButton button) const {
		return MouseButtonDown(button) && (prev_buttons_ & SDL_BUTTON((int)button)) == 0;
	}
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