#ifndef OMEGA_SCENE_SCENE_H
#define OMEGA_SCENE_SCENE_H

#include <string>

#include "lib/entt/entt.hpp"

#include "omega/core/viewport.h"

namespace omega {

class SceneHierarchy;

namespace scene {

class Entity;

class Scene {
  public:
    Scene(const std::string &name = "Main Scene");
    ~Scene();

    /**
     * Create a new entity with a default tag "New Entity"
     * @param tag_name
     */
    Entity create_entity(const std::string &tag_name = "New Entity");

    void render(float dt);
    void update(float dt);

    // getters and setters
    const std::string &get_name() const { return name; }
    entt::registry &get_registry() { return registry; }

    /**
     * Resizes the scene viewport
     * @param width
     * @param height
     */
    void on_resize(uint32_t width, uint32_t height) {
        viewport.on_resize(width, height);
    }

  private:
    std::string name;

    // entities
    entt::registry registry;

    core::Viewport viewport;

    friend class Entity;
    friend class SceneHierarchy;
};
} // namespace scene

} // namespace omega

#endif // OMEGA_SCENE_SCENE_H
