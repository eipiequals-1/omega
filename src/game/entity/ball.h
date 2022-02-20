#ifndef _GAME_ENTITY_BALL_H_
#define _GAME_ENTITY_BALL_H_

#include <iostream>

#include "game/entity/sprite.h"
#include "libGL2D/core/using.h"
#include "libGL2D/gfx/texture/texture.h"

class Ball : public Sprite {
   public:
	Ball(libGL2D::Sptr<libGL2D::Texture> tex, float centerX, float centerY, float radius);
	~Ball() override;

	void Render(libGL2D::SpriteBatch &batch) override;
	void CheckBounds(const glm::rect &bounds);
	void Update(float dt) override;
	void Input(libGL2D::InputProcessor &input, float dt);

	bool IsInHole() const { return inHole; }
	void SetInHole(bool a) {
		inHole = a;
	}
	void SetCenter(float x, float y) {
		rect_.x = x - RADIUS;
		rect_.y = y - RADIUS;
	}

	float GetChargePercent() const { return charge_vel_ / MAX_VEL; }

	void OnBallCollision(Ball &b, float dt) {
		// remove collisions
		while (glm::circleVsCircle(rect_.center(), RADIUS, b.rect_.center(), RADIUS)) {
			if (!b.inHole) {
				b.rect_.translate(-b.vel_ * dt);
			}
			if (!inHole) {
				rect_.translate(-vel_ * dt);
			}
		}

		// find diff vector
		const auto diff = rect_.center() - b.get_rect().center();
		// find normalized diff vector
		const auto unitNormal = glm::normalize(diff);
		// find unit tangent vector
		const auto unitTangent = glm::vec2(-unitNormal.y, unitNormal.x);
		// project velocites ont unit normal and unit tangent vectors
		const float v1normal = glm::dot(unitNormal, vel_);
		const float v1tangent = glm::dot(unitTangent, vel_);
		const float v2normal = glm::dot(unitNormal, b.get_vel());
		const float v2tangent = glm::dot(unitTangent, b.get_vel());

		// find new normal velocities and
		// convert scalar normal and tangential vel into vectors
		glm::vec2 v1normalPrime = unitNormal * v2normal;
		const glm::vec2 v1tangentPrime = unitTangent * v1tangent;
		glm::vec2 v2normalPrime = unitNormal * v1normal;
		const glm::vec2 v2tangentPrime = unitTangent * v2tangent;

		// set new velocities
		vel_ = v1normalPrime + v1tangentPrime;
		b.set_vel(v2normalPrime + v2tangentPrime);
	}

	constexpr static float RESTITUTION = 0.6f;
	constexpr static float FRICTION = 0.95f;  // lose that percentage of vel after 1 sec
	constexpr static float RADIUS = 16.0f;

   private:
	constexpr static float MAX_VEL = 2000.0f;
	constexpr static float CHARGE_ACC = 3000.0f;

	float charge_vel_;
	bool charging;
	bool inHole;
};

#endif  // _GAME_ENTITY_BALL_H_