#ifndef LIBGL2D_UI_UISCREEN_H
#define LIBGL2D_UI_UISCREEN_H

#include <vector>

#include "libGL2D/events/input_processor.h"
#include "libGL2D/physics/math.h"
#include "libGL2D/ui/button/button.h"

namespace libgl {

class UIScreen {
   public:
	UIScreen();
	virtual ~UIScreen();

	void Update(const glm::vec2 &mouse_pos);
	void PushButton(Button *button);
	void HandleButtons();

   protected:
	std::vector<Button *> buttons_;
};
}  // namespace libgl

#endif  // LIBGL2D_UI_UISCREEN_H