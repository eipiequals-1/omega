#ifndef LIBGL2D_EVENTS_INPUTPROCESSOR_H
#define LIBGL2D_EVENTS_INPUTPROCESSOR_H

#include <cstdint>

#include "libGL2D/core/using.h"
#include "libGL2D/events/event.h"
#include "libGL2D/events/input_manager.h"

namespace libgl {

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

}  // namespace libgl

#endif  // LIBGL2D_EVENTS_INPUTPROCESSOR_H