#ifndef OMEGA_UI_BUTTON_TEXTBUTTON_H
#define OMEGA_UI_BUTTON_TEXTBUTTON_H

#include "omega/core/using.h"
#include "omega/gfx/texture/texture.h"
#include "omega/ui/button/image_button.h"
#include "omega/ui/font.h"

namespace omega {

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

	virtual void Render() override;

   protected:
	Uptr<Texture> text_texture_;
	float text_width_, text_height_;
};

}  // namespace omega

#endif  // OMEGA_UI_BUTTON_TEXTBUTTON_H