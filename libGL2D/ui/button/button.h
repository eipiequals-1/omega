#ifndef LIBGL2D_UI_BUTTON_BUTTON_H
#define LIBGL2D_UI_BUTTON_BUTTON_H

#include <functional>

#include "libGL2D/gfx/sprite_batch.h"
#include "libGL2D/physics/math.h"
#include "libGL2D/scene/entity.h"

namespace libgl {
class Button : public RectComponent {
   public:
	Button(float x, float y, float w, float h, std::function<void()> on_click);
	virtual ~Button();

	virtual void Render() = 0;

	bool ContainsPoint(const glm::vec2& p) const {
		return rect_.point_in_rect(p);
	}
	bool GetHover() const { return hover_; }
	void SetHover(bool hover) { hover_ = hover; }

	void OnClick() {
		if (on_click_ != nullptr) {
			on_click_();
		}
	}

   protected:
	std::function<void()> on_click_;
	bool hover_;
};

}  // namespace libgl

#endif  // LIBGL2D_UI_BUTTON_BUTTON_H