#include "text_button.h"

namespace omega::ui::button {

TextButton::TextButton(float x, float y, float w, float h, std::function<void()> on_click, const TextButtonBuilder &builder) : ImageButton(x, y, w, h, on_click), text_texture(nullptr), text_width(builder.width), text_height(builder.height) {
    text_texture = builder.font->render_text(builder.text, builder.color);
}

TextButton::~TextButton() {
}

void TextButton::render() {
    ImageButton::render();
    SpriteBatch &sprite_batch = SpriteBatch::instance();
    sprite_batch.render_texture(text_texture.get(), rect.center().x - text_width / 2.0f, rect.center().y - text_height / 2.0f);
}

} // namespace omega