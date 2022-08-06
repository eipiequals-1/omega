#ifndef OMEGA_SCENE_ENTITY_H
#define OMEGA_SCENE_ENTITY_H

#include <vector>

#include "omega/scene/components.h"

namespace omega {

class Entity {
   public:
	Entity();
	virtual ~Entity();

	template <typename T, typename... Args>
	T &AddComponent(Args &&...args) {
		Component *c = new T(std::forward<Args>(args)...);
		components_.push_back(c);

		c->SetOwner(this);
		component_array_[GetComponentID<T>()] = c;
		component_bitset_[GetComponentID<T>()] = true;
		return *c;
	}

	template <typename T>
	T &GetComponent() {
		Component *c = component_array_[GetComponentID<T>()];
		return *c;
	}

	virtual void Render(float dt);
	virtual void Input(float dt);
	virtual void Update(float dt);

   protected:
	std::vector<Component *> components_;
	ComponentArray component_array_;
	ComponentBitset component_bitset_;
};

}  // namespace omega

#endif  // OMEGA_SCENE_ENTITY_H