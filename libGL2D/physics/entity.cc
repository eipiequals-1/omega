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
}