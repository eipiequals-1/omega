#ifndef _LIBGL2D_PHYSICS_ENTITY_H_
#define _LIBGL2D_PHYSICS_ENTITY_H_

#include "libGL2D/events/input_processor.h"
#include "libGL2D/gfx/sprite_batch.h"
#include "libGL2D/gfx/texture/texture.h"
#include "libGL2D/physics/math.h"

namespace libgl {

/**
 * Basic Entity abstraction for rendering, updating, and handling inputs
 */
class Entity {
   public:
	Entity();
	virtual ~Entity() {}

	/**
	 * Updates the entity data
	 * @param dt the timestep if necessary
	 */
	virtual void Update(float dt) {
		(void)dt;
	}

	/**
	 * Renders the entity
	 * @param sprite_batch for rendering
	 */
	virtual void Render(SpriteBatch &sprite_batch) {
		(void)sprite_batch;
	}

	/**
	 * Handles input and stores entity data
	 * @param input the input processor to get data from
	 */
	virtual void Input(InputProcessor &input) {
		(void)input;
	}
	virtual const glm::vec2 &get_vel() const { return vel_; }
	virtual void set_vel(const glm::vec2 &vel) { vel_ = vel; }
	virtual void set_vel_x(float x) { vel_.x = x; }
	virtual void set_vel_y(float y) { vel_.y = y; }

   protected:
	glm::vec2 vel_;
};

/**
 * Abstraction for entities if they are circles
 */
class CircleComponent {
   public:
	CircleComponent(float x, float y, float radius);
	const glm::vec2 &get_center() const { return center_; }
	float get_radius() const { return radius_; }

   protected:
	glm::vec2 center_;
	float radius_;
};

/**
 * Abstraction for AABB rectangle entities
 */
class RectComponent {
   public:
	RectComponent(float x, float y, float w, float h);
	const glm::rect &get_rect() const { return rect_; }
	void set_x(float x) { rect_.x = x; }
	void set_y(float y) { rect_.y = y; }
	void set_w(float w) { rect_.w = w; }
	void set_h(float h) { rect_.h = h; }
	void set_rect(const glm::rect &r) { rect_ = r; }

   protected:
	glm::rect rect_;
};

/**
 * Abstraction of a texture using / sprite rendering entity
 */
class SpriteComponent {
   public:
	SpriteComponent(Texture *texture);

   protected:
	Texture *texture_;
};

}  // namespace libgl

#endif  // _LIBGL2D_PHYSICS_ENTITY_H_