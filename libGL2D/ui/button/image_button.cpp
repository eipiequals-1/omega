#include "image_button.h"

namespace libgl {

ImageButton::ImageButton(float x, float y, float w, float h, std::function<void()> on_click) : Button::Button(x, y, w, h, on_click), focus_(nullptr), un_focus_(nullptr) {
}

ImageButton::~ImageButton() {
	focus_ = nullptr;
	un_focus_ = nullptr;
}

void ImageButton::Render() {
	SpriteBatch& sprite_batch = SpriteBatch::Instance();
	if (hover_) {
		if (focus_ != nullptr) {
			sprite_batch.RenderTexture(focus_, rect_.x, rect_.y, rect_.w, rect_.h);
		}
	} else {
		if (un_focus_ != nullptr) {
			sprite_batch.RenderTexture(un_focus_, rect_.x, rect_.y, rect_.w, rect_.h);
		}
	}
}
}  // namespace libgl
