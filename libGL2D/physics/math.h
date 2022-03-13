#ifndef _LIBGL2D_PHYSICS_MATH_H_
#define _LIBGL2D_PHYSICS_MATH_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

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

const glm::vec4 WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const glm::vec4 BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 RED(1.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const glm::vec4 BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const glm::vec4 YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
}  // namespace glm

#endif  // _LIBGL2D_PHYSICS_MATH_H_