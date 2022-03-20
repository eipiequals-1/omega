#ifndef _LIBGL2D_EVENTS_INPUTPROCESSOR_H_
#define _LIBGL2D_EVENTS_INPUTPROCESSOR_H_

#include <SDL2/SDL.h>

#include "libGL2D/events/key_processor.h"
#include "libGL2D/physics/math.h"

namespace libGL2D {

using Event = SDL_Event;

enum class EventType {
	kQuit = SDL_QUIT,
	kWindowEvent = SDL_WINDOWEVENT
};

class InputProcessor {
   public:
	InputProcessor();
	void PrepareForUpdate();
	bool PollEvents(Event &event);
	void Update();

	KeyProcessor &GetKeyProcessor() { return key_processor_; }
	const glm::vec2 &GetMousePos() const { return mouse_pos_; }
	bool LeftIsDown() const {
		return (buttons_ & SDL_BUTTON(SDL_BUTTON_LEFT)) == 1;
	}

   private:
	KeyProcessor key_processor_;
	glm::vec2 mouse_pos_;  // mousePos relative to top left
	uint32_t buttons_;
};

}  // namespace libGL2D

#endif  // _LIBGL2D_EVENTS_INPUTPROCESSOR_H_