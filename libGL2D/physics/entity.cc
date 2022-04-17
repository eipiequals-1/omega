#include "entity.h"

namespace libgl {

Entity::Entity() : vel_(0.0f, 0.0f) {
}

CircleComponent::CircleComponent(float x, float y, float radius) : center_(x, y), radius_(radius) {
}

RectComponent::RectComponent(float x, float y, float w, float h) : rect_(x, y, w, h) {
}

SpriteComponent::SpriteComponent(Texture *texture) : texture_(texture) {
}

void RectComponent::OnLeftCollision(float left_bound) {
	rect_.x = left_bound;
}

void RectComponent::OnRightCollision(float right_bound) {
	rect_.x = right_bound - rect_.y;
}

void RectComponent::OnTopCollision(float top_bound) {
	rect_.y = top_bound - rect_.h;
}

void RectComponent::OnBottomCollision(float bottom_bound) {
	rect_.y = bottom_bound;
}
}