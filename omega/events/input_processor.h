#ifndef OMEGA_EVENTS_INPUTPROCESSOR_H
#define OMEGA_EVENTS_INPUTPROCESSOR_H

#include <cstdint>

#include "omega/events/event.h"
#include "omega/events/input_manager.h"
#include "omega/util/util.h"

namespace omega {

class InputProcessor {
   public:
	InputProcessor();
	virtual ~InputProcessor();

	void Listen();
	// mouse and key input
	virtual void OnKeyDown(Key key) = 0;
	virtual void OnKeyUp(Key key) = 0;
	virtual void OnMouseDown(uint32_t screen_x, uint32_t screen_y, MouseButton button) = 0;
	virtual void OnMouseUp(uint32_t screen_x, uint32_t screen_y, MouseButton button) = 0;
	// window input
	virtual void OnWindowResize(uint32_t window_width, uint32_t window_height) = 0;
	virtual void OnWindowClosed() = 0;
};

}  // namespace omega

#endif  // OMEGA_EVENTS_INPUTPROCESSOR_H