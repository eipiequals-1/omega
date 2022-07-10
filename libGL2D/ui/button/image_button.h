#ifndef LIBGL2D_UI_BUTTON_IMAGEBUTTON_H
#define LIBGL2D_UI_BUTTON_IMAGEBUTTON_H

#include "libGL2D/core/using.h"
#include "libGL2D/gfx/texture/texture.h"
#include "libGL2D/ui/button/button.h"

namespace libgl {
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

}  // namespace libgl

#endif  // LIBGL2D_UI_BUTTON_IMAGEBUTTON_H