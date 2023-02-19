#ifndef OMEGA_SCENE_ENTITY_HPP
#define OMEGA_SCENE_ENTITY_HPP

#include <vector>

#include "lib/entt/entt.hpp"

namespace omega::scene {

/**
 * Represents an entity in the scene
 */
class Entity {
  public:
    Entity() = default;

    Entity(entt::entity handle, entt::registry *registry) : entity(handle),
                                                            registry(registry) {}

    Entity(const Entity &other) = default;

    ~Entity() = default;

    /**
     * Create a component of type T
     * @param args any arguments to create the component
     */
    template <typename T, typename... Args>
    T &add_component(Args &&...args) {
        return registry->emplace<T>(entity, std::forward<Args>(args)...);
    }

    /**
     * Get a component of type T
     */
    template <typename T>
    T &get_component() {
        return registry->get<T>(entity);
    }

    /**
     * Return if there exists a component of type T
     */
    template <typename T>
    bool has_component() {
        return registry->has<T>(entity);
    }

    /**
     * Remove a component of type T
     */
    template <typename T>
    void remove_component() {
        registry->remove<T>(entity);
    }

    /**
     * @return if the entity id's are equal
     */
    bool operator==(Entity other) const {
        return entity == other.entity;
    }

    /**
     * Convert an entity to an uint32_t id
     */
    operator uint32_t() const {
        return (uint32_t)entity;
    }
    operator entt::entity() const { return entity; }

    /**
     * @return if the entity is not null
     */
    operator bool() const { return entity != entt::null; }

  protected:
    entt::entity entity{entt::null};
    entt::registry *registry = nullptr;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_ENTITY_HPP
