#include "text_button.hpp"

#include "omega/gfx/sprite_batch.hpp"

namespace omega::ui::button {

TextButton::TextButton(float x, float y, float w, float h, std::function<void()> on_click, const TextButtonBuilder &builder) : ImageButton(x, y, w, h, on_click), text_texture(nullptr), text_width(builder.width), text_height(builder.height) {
    text_texture = builder.font->render_text(builder.text, builder.color);
}

void TextButton::render() {
    ImageButton::render();
}

} // namespace omega
