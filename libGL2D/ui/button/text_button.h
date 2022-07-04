#ifndef LIBGL2D_UI_BUTTON_TEXTBUTTON_H
#define LIBGL2D_UI_BUTTON_TEXTBUTTON_H

#include "libGL2D/core/using.h"
#include "libGL2D/gfx/texture/texture.h"
#include "libGL2D/ui/button/image_button.h"
#include "libGL2D/ui/font.h"

namespace libgl {

struct TextButtonBuilder {
	std::string text;
	Font *font;
	float width, height;
	glm::vec4 color;
};

class TextButton : public ImageButton {
   public:
	TextButton(float x, float y, float w, float h, std::function<void()> on_click, const TextButtonBuilder &builder);
	virtual ~TextButton() override;

	virtual void Render(SpriteBatch &sprite_batch) override;

   protected:
	Uptr<Texture> text_texture_;
	float text_width_, text_height_;
};

}  // namespace libgl

#endif  // LIBGL2D_UI_BUTTON_TEXTBUTTON_H