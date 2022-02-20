#include "ball.h"

#include "billiards/game_data.h"

Ball::Ball(libGL2D::Sptr<libGL2D::Texture> tex, float centerX, float centerY, float radius) : Sprite(tex) {
	rect_.w = radius * 2;
	rect_.h = radius * 2;
	rect_.x = centerX - rect_.w / 2;
	rect_.y = centerY - rect_.h / 2;
	charging = false;
	charge_vel_ = 0.0f;
	inHole = false;
}

Ball::~Ball() {
}

void Ball::Render(libGL2D::SpriteBatch &batch) {
	batch.Render(texture_.get(), rect_.x, rect_.y, rect_.w, rect_.h);
}

void Ball::CheckBounds(const glm::rect &bounds) {
	if (rect_.x < bounds.x) {
		rect_.x = bounds.x;
		vel_.x *= -RESTITUTION;
	} else if (rect_.x + rect_.w > bounds.x + bounds.w) {
		rect_.x = bounds.x + bounds.w - rect_.w;
		vel_.x *= -RESTITUTION;
	}
	if (rect_.y < bounds.y) {
		rect_.y = bounds.y;
		vel_.y *= -RESTITUTION;
	} else if (rect_.y + rect_.h > bounds.y + bounds.h) {
		rect_.y = bounds.y + bounds.h - rect_.h;
		vel_.y *= -RESTITUTION;
	}
}

void Ball::Update(float dt) {
	if (!inHole) {
		rect_.translate(vel_ * dt);

		// apply friction
		if (vel_.x * vel_.x + vel_.y * vel_.y >= 1.0f) {
			vel_ -= vel_ * FRICTION * dt;
		}
	}
}

void Ball::Input(libGL2D::InputProcessor &input, float dt) {
	(void)dt;
	libGL2D::KeyProcessor &kp = input.GetKeyProcessor();
	if (kp.KeyHeld(SDL_SCANCODE_SPACE)) {
		charging = true;
		charge_vel_ += CHARGE_ACC * dt;
		if (charge_vel_ > MAX_VEL) {
			charge_vel_ = MAX_VEL;
		}
	} else {
		if (charging) {
			charging = false;

			// calculate new velocity
			glm::vec2 mp = input.GetMousePos();
			mp.y = GameData::HEIGHT - mp.y;
			glm::vec2 diff = mp - glm::vec2(rect_.x + rect_.w / 2.0f, rect_.y + rect_.h / 2.0f);
			vel_ = glm::normalize(diff) * charge_vel_;

			charge_vel_ = 0.0f;
		}
	}
}
