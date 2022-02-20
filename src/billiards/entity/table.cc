#include "table.h"

Table::Table(libGL2D::Sptr<libGL2D::Texture> texture, float win_width, float win_height) : Sprite(texture) {
	// height / texHeight = width / texWidth
	rect_.h = win_height * 0.8f;
	rect_.w = texture_->GetWidth() * rect_.h / texture_->GetHeight();
	rect_.x = win_width / 2.0f - rect_.w / 2.0f;
	rect_.y = win_height / 2.0f - rect_.h / 2.0f;
}
