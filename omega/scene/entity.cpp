#include "entity.h"

namespace omega {

Entity::Entity() {
}

Entity::~Entity() {
	for (Component *c : components_) {
		delete c;
		c = nullptr;
	}
}

void Entity::Render(float dt) {
	components_[0]->Render(dt);
	// for (Component *c : components_) {
	// 	c->Render(dt);
	// }
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