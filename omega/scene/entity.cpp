#include "entity.h"

namespace omega {

Entity::Entity() {
}

void Entity::Render(float dt) {
	for (Component *c : components_) {
		c->Render(dt);
	}
}

void Entity::Update(float dt) {
	for (Component *c : components_) {
		c->Update(dt);
	}
}

void Entity::Input(float dt) {
	for (Component *c : components_) {
		c->Input(dt);
	}
}

}  // namespace omega