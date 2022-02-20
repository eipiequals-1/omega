#ifndef _LIBGL2D_PHYSICS_ENTITY_ENTITY_H_
#define _LIBGL2D_PHYSICS_ENTITY_ENTITY_H_

#include "libGL2D/events/input_processor.h"
#include "libGL2D/gfx/sprite_batch.h"
#include "libGL2D/gfx/texture/texture.h"
#include "libGL2D/physics/math.h"

namespace libGL2D {

class Entity {
   public:
	Entity();
	virtual void Update(float dt) {
		(void)dt;
	}
	virtual void Render(SpriteBatch &sprite_batch) {
		(void)sprite_batch;
	}
	virtual void Input(InputProcessor &input) {
		(void)input;
	}
	virtual const glm::vec2 &get_vel() const { return vel_; }
	virtual void set_vel(const glm::vec2 &vel) { vel_ = vel; }

   private:
	glm::vec2 vel_;
};

class CircleComponent {
   public:
	CircleComponent(float x, float y, float radius);

   protected:
	glm::vec2 center_;
	float radius_;
};

class RectComponent {
   public:
	RectComponent(float x, float y, float w, float h);

   protected:
	glm::rect rect_;
};

class SpriteComponent {
   public:
	SpriteComponent(Texture *texture);

   protected:
	Texture *texture_;
};

}  // namespace libGL2D

#endif  // _LIBGL2D_PHYSICS_ENTITY_ENTITY_H_