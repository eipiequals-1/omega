#include "scene.hpp"

#include "omega/gfx/gl.hpp"
#include "omega/scene/components.hpp"
#include "omega/scene/entity.hpp"
#include "omega/util/color.hpp"
#include "omega/util/math.hpp"

namespace omega::scene {

entt::registry Scene::registry;

Scene::Scene(const core::Viewport &viewport, const std::string &name)
 : name(name),
   viewport(viewport) {
}

Scene::~Scene() {
}

Entity Scene::create_entity() {
    Entity ent(registry.create());
    return ent;
}

void Scene::render(f32 dt, gfx::SpriteBatch &sprite_batch) {
    (void)dt;
   // get camera for rendering
    Camera *scene_camera = nullptr;
    auto view = registry.view<CameraComponent>();
    for (auto entity : view) {
        auto &camera = Entity(entity).get_component<CameraComponent>();

        if (camera.primary) {
            scene_camera = (camera.get_projection_type() ==
                CameraComponent::ProjectionType::orthographic ?
                (Camera *)&camera.ortho : (Camera *)&camera.perspective);
            break;
        }
    }

    // render scene if a camera was found
    if (scene_camera == nullptr) {
        return;
    }

    // obtain sprite batch instance and render every entity
    // with a sprite & transform component
    scene_camera->recalculate_view_matrix();

    sprite_batch.set_view_projection_matrix(
        scene_camera->get_view_projection_matrix());
    sprite_batch.begin_render();

    auto group = registry.group<TransformComponent>(entt::get<SpriteComponent>);
    for (auto entity : group) {
        auto [transform, sprite] =
            group.get<TransformComponent, SpriteComponent>(entity);

        // make sure that there is a valid texture
        if (sprite.texture == nullptr)
            continue;

        // construct necessary rectangles for rendering
        glm::rectf dest(
            transform.position.x - transform.scale.x * 0.5f,
            transform.position.y - transform.scale.y * 0.5f,
            transform.scale.x,
            transform.scale.y);

        sprite_batch.render_texture(
            sprite.texture,
            glm::rectf(0.0f,
                       0.0f,
                       sprite.texture->get_width(),
                       sprite.texture->get_height()),
            dest,
            transform.rotation.z,
            dest.center(),
            sprite.color);
    }
    sprite_batch.end_render();
}

void Scene::update(f32 dt) {
    auto view = registry.view<TransformComponent, MoveComponent>();
    view.each([&](TransformComponent &transform, MoveComponent &move) {
        // v = at + v0
        // => v += a * dt * 0.5f = avg (v on [t0, t1])
        // => x += v * dt = intagral of v from t0 to t1
        // update v
        // v += a * dt * 0.5f
        move.velocity += move.acceleration * dt * 0.5f;
        transform.position += move.velocity * dt;
        move.velocity += move.acceleration * dt * 0.5f;
    });
}

} // namespace omega::scene
