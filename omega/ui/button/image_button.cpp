#include "image_button.hpp"

#include "omega/gfx/sprite_batch.hpp"

namespace omega::ui::button {

ImageButton::ImageButton(float x, float y, float w, float h, std::function<void()> on_click) : Button::Button(x, y, w, h, on_click), focus(nullptr), un_focus(nullptr) {
}

ImageButton::~ImageButton() {
    focus = nullptr;
    un_focus = nullptr;
}

void ImageButton::render() {
    gfx::SpriteBatch &sprite_batch = gfx::SpriteBatch::instance();
    if (hover) {
        if (focus != nullptr) {
            sprite_batch.render_texture(focus, rect.x, rect.y, rect.w, rect.h);
        }
    } else {
        if (un_focus != nullptr) {
            sprite_batch.render_texture(un_focus, rect.x, rect.y, rect.w, rect.h);
        }
    }
}
} // namespace omega::ui::button
