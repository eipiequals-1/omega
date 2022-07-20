#ifndef OMEGA_UI_BUTTON_BUTTON_H
#define OMEGA_UI_BUTTON_BUTTON_H

#include <functional>

#include "omega/gfx/sprite_batch.h"
#include "omega/physics/math.h"
#include "omega/scene/entity.h"

namespace omega {
class Button : public RectComponent {
   public:
	Button(float x, float y, float w, float h, std::function<void()> on_click);
	virtual ~Button();

	virtual void Render() = 0;
	void Render(float dt) override {
		(void)dt;
		Render();
	}

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

}  // namespace omega

#endif  // OMEGA_UI_BUTTON_BUTTON_H