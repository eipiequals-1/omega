#ifndef _LIBGL2D_PHYSICS_MATH_H_
#define _LIBGL2D_PHYSICS_MATH_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace libgl {
enum class Direction {
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3
};
}

namespace glm {

struct rect {
   public:
	float x, y, w, h;

	rect(float x, float y, float w, float h);
	rect();
	virtual void translate(const glm::vec2 &a) {
		x += a.x;
		y += a.y;
	}
	glm::vec2 center() const {
		return glm::vec2(x + w / 2.0f, y + h / 2.0f);
	}
	void set_center_x(float centerx) {
		x = centerx - w / 2.0f;
	}
	void set_center_y(float centery) {
		y = centery - h / 2.0f;
	}
	virtual bool overlaps(const rect &a) {
		return x < a.x + a.w && x + w > a.x && y < a.y + a.h && y + h > a.y;
	}
	virtual bool point_in_rect(const vec2 &p) {
		return x < p.x && p.x < x + w && y < p.y && p.y < y + h;
	}
	virtual void print() const {
		printf("x=%f, y=%f, w=%f, h=%f\n", x, y, w, h);
	}
	virtual bool operator==(const rect &a) const {
		return a.x == x && a.y == y && a.w == w && a.h == h;
	}
	virtual bool operator!=(const rect &a) const {
		return !(a == *this);
	}
};

bool circleVsCircle(const glm::vec2 &center1, float radius1, const glm::vec2 &center2, float radius2);

const vec4 kWhite(1.0f, 1.0f, 1.0f, 1.0f);
const vec4 kBlack(0.0f, 0.0f, 0.0f, 1.0f);
const vec4 kRed(1.0f, 0.0f, 0.0f, 1.0f);
const vec4 kGreen(0.0f, 1.0f, 0.0f, 1.0f);
const vec4 kBlue(0.0f, 0.0f, 1.0f, 1.0f);
const vec4 kYellow(1.0f, 1.0f, 0.0f, 1.0f);
}  // namespace glm

#endif  // _LIBGL2D_PHYSICS_MATH_H_