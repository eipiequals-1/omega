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

static constexpr std::size_t kMaxEntities = 5000;
static constexpr std::size_t kMaxComponents = 32;

using ComponentBitset = std::bitset<kMaxEntities>;
using ComponentArray = std::array<Component *, kMaxEntities>;

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

    const glm::rectf &GetRect() const { return rect; }
    void SetRect(const glm::rectf &rect) { this->rect = rect; }

    float GetRotation() const { return rotation; }
    void SetRotation(float rotation) { this->rotation = rotation; }

  protected:
    glm::rectf rect;
    float rotation; // in degrees
};

class SpriteComponent : public RectComponent {
  public:
    SpriteComponent() {
        color = omega::util::color::white;
    }

    Texture *GetTexture() { return texture; }
    void SetTexture(Texture *texture) { this->texture = texture; }

    const glm::vec4 &GetColor() { return color; }
    void SetColor(const glm::vec4 &color) { this->color = color; }

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