#include "entity.h"

namespace omega::scene {

Entity::Entity() {
}

Entity::~Entity() {
    for (Component *c : components) {
        delete c;
        c = nullptr;
    }
}

void Entity::render(f32 dt) {
    for (Component *c : components) {
        c->render(dt);
    }
}

void Entity::update(f32 dt) {
    for (Component *c : components) {
        c->update(dt);
    }
}

void Entity::input(f32 dt) {
    for (Component *c : components) {
        c->input(dt);
    }
}

} // namespace omega::scene