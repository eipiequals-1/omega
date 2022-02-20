#ifndef _GAME_ENTITY_SPRITE_H_
#define _GAME_ENTITY_SPRITE_H_

#include <memory>

#include "libGL2D/core/using.h"
#include "libGL2D/events/input_processor.h"
#include "libGL2D/gfx/sprite_batch.h"
#include "libGL2D/gfx/texture/texture.h"
#include "libGL2D/physics/math.h"

class Sprite {
   public:
	Sprite(libGL2D::Sptr<libGL2D::Texture> tex);
	virtual ~Sprite();
	virtual void Render(libGL2D::SpriteBatch &batch) { batch.Render(texture_.get(), rect_.x, rect_.y, rect_.w, rect_.h); }
	virtual void Update(float dt) { (void)dt; }
	virtual void Input(libGL2D::InputProcessor &input) { (void)input; }

	virtual const glm::rect &get_rect() const { return rect_; }
	virtual const glm::vec2 &get_vel() const { return vel_; }

	virtual void set_vel(const glm::vec2 &v) {
		vel_.x = v.x;
		vel_.y = v.y;
	}

   protected:
	glm::rect rect_;
	glm::vec2 vel_;
	libGL2D::Sptr<libGL2D::Texture> texture_;

   private:
};

#endif  // _GAME_ENTITY_SPRITE_H_