#ifndef OMEGA_SCENE_COMPONENTS_H
#define OMEGA_SCENE_COMPONENTS_H

#include <array>
#include <bitset>

#include "omega/gfx/sprite_batch.h"
#include "omega/gfx/texture/texture.h"
#include "omega/physics/math.h"

namespace omega {

class Entity;
class Component;

using ComponentID = std::size_t;

inline ComponentID GetUniqueComponentID() {
	static ComponentID id = 0;
	return id++;
}

template <typename T>
inline ComponentID GetComponentID() {
	static const ComponentID type_id = GetUniqueComponentID();
	return type_id;
}

static constexpr std::size_t kMaxEntities = 5000;
static constexpr std::size_t kMaxComponents = 32;

using ComponentBitset = std::bitset<kMaxEntities>;
using ComponentArray = std::array<Component *, kMaxEntities>;

class Component {
   public:
	Component() : owner_(nullptr) {}
	virtual ~Component() = default;

	Entity *GetOwner() { return owner_; }
	void SetOwner(Entity *owner) { owner_ = owner; }

	virtual void Render(float dt) { (void)dt; }
	virtual void Input(float dt) { (void)dt; }
	virtual void Update(float dt) { (void)dt; }

   protected:
	Entity *owner_;
};

class RectComponent : public Component {
   public:
	RectComponent() { rotation_ = 0; }

	const glm::rectf &GetRect() const { return rect_; }
	void SetRect(const glm::rectf &rect) { rect_ = rect; }

	float GetRotation() const { return rotation_; }
	void SetRotation(float rotation) { rotation_ = rotation; }

   protected:
	glm::rectf rect_;
	float rotation_;  // in degrees
};

class SpriteComponent : public RectComponent {
   public:
	SpriteComponent() {
		color_ = glm::kWhite;
	}

	Texture *GetTexture() { return texture_; }
	void SetTexture(Texture *texture) { texture_ = texture; }

	const glm::vec4 &GetColor() { return color_; }
	void SetColor(const glm::vec4 &color) { color_ = color; }

	virtual void Render(float dt) override {
		(void)dt;
		SpriteBatch &batch = SpriteBatch::Instance();
		batch.RenderTexture(texture_, glm::rectf(0.0f, 0.0f, texture_->GetWidth(), texture_->GetHeight()), rect_, rotation_, rect_.center());
	}

   protected:
	Texture *texture_;
	glm::vec4 color_;
};

}  // namespace omega

#endif  // OMEGA_SCENE_COMPONENTS_H