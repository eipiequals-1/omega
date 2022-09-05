#ifndef OMEGA_UI_UISCREEN_H
#define OMEGA_UI_UISCREEN_H

#include <vector>

#include "omega/events/input_processor.h"
#include "omega/ui/button/button.h"
#include "omega/util/util.h"

namespace omega {

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
}  // namespace omega

#endif  // OMEGA_UI_UISCREEN_H