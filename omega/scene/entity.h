#ifndef OMEGA_SCENE_ENTITY_H
#define OMEGA_SCENE_ENTITY_H

#include <vector>

#include "omega/scene/components.h"

namespace omega::scene {

class Entity {
  public:
    Entity();
    virtual ~Entity();

    template <typename T, typename... Args>
    T &add_component(Args &&...args) {
        T *c = new T(std::forward<Args>(args)...);
        components.push_back(c);

        c->set_owner(this);
        component_array[get_component_id<T>()] = c;
        component_bitset[get_component_id<T>()] = true;
        return *c;
    }
    template <typename T>
    T &get_component() {
        Component *c = component_array[get_component_id<T>()];
        return static_cast<T>(*c);
    }
    void render(f32 dt);
    virtual void input(f32 dt);
    virtual void update(f32 dt);

  protected:
    std::vector<Component *> components;
    ComponentArray component_array;
    ComponentBitset component_bitset;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_ENTITY_H