#ifndef OMEGA_SCENE_ENTITY_H
#define OMEGA_SCENE_ENTITY_H

#include <vector>

#include "omega/vendor/entt/entt.hpp"

namespace omega::scene {

class Entity {
  public:
    Entity() = default;

    Entity(entt::entity handle, entt::registry *registry) : entity(handle),
                                                            registry(registry) {}

    Entity(const Entity &other) = default;

    ~Entity() = default;

    template <typename T, typename... Args>
    T &add_component(Args &&...args) {
        return registry->emplace<T>(entity, std::forward<Args>(args)...);
    }

    template <typename T>
    T &get_component() {
        return registry->get<T>(entity);
    }

    template <typename T>
    bool has_component() {
        return registry->has<T>(entity);
    }

    template <typename T>
    void remove_component() {
        registry->remove<T>(entity);
    }

    bool operator==(Entity other) const {
        return entity == other.entity;
    }

    operator uint32_t() const {
        return (uint32_t)entity;
    }
    operator entt::entity() const { return entity; }
    operator bool() const { return entity != entt::null; }

  protected:
    entt::entity entity{entt::null};
    entt::registry *registry = nullptr;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_ENTITY_H