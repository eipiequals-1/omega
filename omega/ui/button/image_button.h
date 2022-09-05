#ifndef OMEGA_UI_BUTTON_IMAGEBUTTON_H
#define OMEGA_UI_BUTTON_IMAGEBUTTON_H

#include "omega/gfx/texture/texture.h"
#include "omega/ui/button/button.h"
#include "omega/util/util.h"

namespace omega {
class ImageButton : public Button {
   public:
	ImageButton(float x, float y, float w, float h, std::function<void()> on_click);
	virtual ~ImageButton() override;

	virtual void Render() override;
	virtual void SetFocusTexture(Texture* focus) { focus_ = focus; }
	virtual void SetUnFocusTexture(Texture* un_focus) { un_focus_ = un_focus; }

   protected:
	Texture* focus_;
	Texture* un_focus_;
};

}  // namespace omega

#endif  // OMEGA_UI_BUTTON_IMAGEBUTTON_H