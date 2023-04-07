#ifndef OMEGA_SCENE_SCENE_HPP
#define OMEGA_SCENE_SCENE_HPP

#include <string>

#include "lib/entt/entt.hpp"

#include "omega/core/viewport.hpp"
#include "omega/gfx/sprite_batch.hpp"

namespace omega::scene {

class Entity;

class Scene {
  public:
    Scene(const core::Viewport &viewport,
          const std::string &name = "Main Scene");
    ~Scene();

    /**
     * Create a new entity with a default tag "New Entity"
     * @param tag_name
     */
    Entity create_entity(const std::string &tag_name = "New Entity");

    void render(float dt, gfx::SpriteBatch &sprite_batch);
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
};

} // namespace omega::scene

#endif // OMEGA_SCENE_SCENE_HPP
