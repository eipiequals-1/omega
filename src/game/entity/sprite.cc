#include "sprite.h"

Sprite::Sprite(libGL2D::Sptr<libGL2D::Texture> tex) : rect_(0.0f, 0.0f, 0.0f, 0.0f), vel_(0.0f, 0.0f), texture_(tex) {
}

Sprite::~Sprite() {
}
