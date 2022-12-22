#ifndef OMEGA_SCENE_COMPONENTS_H
#define OMEGA_SCENE_COMPONENTS_H

#include <array>
#include <bitset>

#include "omega/gfx/sprite_batch.h"
#include "omega/gfx/texture/texture.h"
#include "omega/util/util.h"

namespace omega::scene {

using namespace omega::gfx;
using namespace omega::gfx::texture;

class Entity;
class Component;

using ComponentID = std::size_t;

inline ComponentID get_unique_component_id() {
    static ComponentID id = 0;
    return id++;
}

template <typename T>
inline ComponentID get_component_id() {
    static const ComponentID type_id = get_unique_component_id();
    return type_id;
}

static constexpr std::size_t max_entities = 5000;
static constexpr std::size_t max_components = 32;

using ComponentBitset = std::bitset<max_components>;
using ComponentArray = std::array<Component *, max_components>;

class Component {
  public:
    Component() : owner(nullptr) {}
    virtual ~Component() = default;

    Entity *get_owner() { return owner; }
    void set_owner(Entity *owner) { this->owner = owner; }

    virtual void render(float dt) { (void)dt; }
    virtual void input(float dt) { (void)dt; }
    virtual void update(float dt) { (void)dt; }

  protected:
    Entity *owner;
};

class RectComponent : public Component {
  public:
    RectComponent() { rotation = 0; }

    const glm::rectf &get_rect() const { return rect; }
    void set_rect(const glm::rectf &rect) { this->rect = rect; }

    float get_rotation() const { return rotation; }
    void set_rotation(float rotation) { this->rotation = rotation; }

  protected:
    glm::rectf rect;
    float rotation; // in degrees
};

class SpriteComponent : public RectComponent {
  public:
    SpriteComponent() {
        color = omega::util::color::white;
    }

    Texture *get_texture() { return texture; }
    void set_texture(Texture *texture) { this->texture = texture; }

    const glm::vec4 &get_color() { return color; }
    void set_color(const glm::vec4 &color) { this->color = color; }

    virtual void render(float dt) override {
        (void)dt;
        SpriteBatch &batch = SpriteBatch::instance();
        batch.render_texture(texture, glm::rectf(0.0f, 0.0f, texture->get_width(), texture->get_height()), rect, rotation, rect.center());
    }

  protected:
    Texture *texture;
    glm::vec4 color;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_COMPONENTS_H