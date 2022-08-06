#include "text_button.h"

namespace omega {

TextButton::TextButton(float x, float y, float w, float h, std::function<void()> on_click, const TextButtonBuilder& builder) : ImageButton(x, y, w, h, on_click), text_texture_(nullptr), text_width_(builder.width), text_height_(builder.height) {
	text_texture_ = builder.font->RenderText(builder.text, builder.color);
}

TextButton::~TextButton() {
}

void TextButton::Render() {
	ImageButton::Render();
	SpriteBatch& sprite_batch = SpriteBatch::Instance();
	sprite_batch.RenderTexture(text_texture_.get(), rect_.center().x - text_width_ / 2.0f, rect_.center().y - text_height_ / 2.0f);
}

}  // namespace omega