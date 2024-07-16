#ifndef OMEGA_SCENE_SCENE_HPP
#define OMEGA_SCENE_SCENE_HPP

#include <entt/entt.hpp>
#include <string>

#include "omega/core/viewport.hpp"
#include "omega/gfx/sprite_batch.hpp"
#include "omega/util/types.hpp"

namespace omega::scene {

class Entity;

class Scene {
  public:
    static entt::registry registry;

    std::string name;
    core::Viewport viewport;

    Scene(const core::Viewport &viewport,
          const std::string &name = "Main Scene");
    ~Scene();

    /**
     * Create a new entity
     */
    Entity create_entity();

    void render(f32 dt, gfx::SpriteBatch &sprite_batch);
    void update(f32 dt);

    /**
     * Resizes the scene viewport
     * @param width
     * @param height
     */
    void on_resize(u32 width, u32 height) {
        viewport.on_resize(width, height);
    }
};

} // namespace omega::scene

#endif // OMEGA_SCENE_SCENE_HPP
