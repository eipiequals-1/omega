#ifndef _LIBGL2D_PHYSICS_MATH_H_
#define _LIBGL2D_PHYSICS_MATH_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace libgl {
/**
 * Abstraction of Direction for game logic
 */
enum class Direction {
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3
};
}  // namespace libgl

namespace glm {

/**
 * Rectangle struct storing x, y, w (width), h (height)
 */
struct rect {
   public:
	float x, y, w, h;

	rect(float x, float y, float w, float h);
	rect();

	/**
	 * Shifts the rectangle by the given vector
	 * @param a the amount to shift
	 */
	virtual void translate(const glm::vec2 &a) {
		x += a.x;
		y += a.y;
	}

	/**
	 * @return the center of the rectangle
	 */
	glm::vec2 center() const {
		return glm::vec2(x + w / 2.0f, y + h / 2.0f);
	}
	void set_center_x(float centerx) {
		x = centerx - w / 2.0f;
	}
	void set_center_y(float centery) {
		y = centery - h / 2.0f;
	}

	/**
	 * Returns if two rectangles overlap using AABB logic
	 * @param a the other rect
	 * @return if they overlap
	 */
	virtual bool overlaps(const rect &a) const {
		return x < a.x + a.w && x + w > a.x && y < a.y + a.h && y + h > a.y;
	}

	/**
	 * Returns if a point is contained in the rectangle
	 * @param p a vec2 representing the point
	 * @return if the point is contained
	 */
	virtual bool point_in_rect(const vec2 &p) const {
		return x < p.x && p.x < x + w && y < p.y && p.y < y + h;
	}

	/**
	 * Prints the rectangle data for debugging purposes
	 */
	virtual void print() const {
		printf("x=%f, y=%f, w=%f, h=%f\n", x, y, w, h);
	}

	/**
	 * @param a another rect
	 * @return if the position and sizes are exactly the same
	 */
	virtual bool operator==(const rect &a) const {
		return a.x == x && a.y == y && a.w == w && a.h == h;
	}

	/**
	 * @param a another rect
	 * @return if the rectangles are not equal
	 */
	virtual bool operator!=(const rect &a) const {
		return !(a == *this);
	}
};

/**
 * Checks collisions between two circles and returns if there is one
 * @param center1 circle1 center
 * @param radius1 circle1 radius
 * @param center2 circle2 center
 * @param radius2 circle2 radius
 * @return if they intersect
 */
bool circleVsCircle(const glm::vec2 &center1, float radius1, const glm::vec2 &center2, float radius2);

/**
 * Returns the distance squared between two points to avoid unnecessary and slow sqrts
 * @param p1 point1
 * @param p2 point2
 * @return the distance squared
 */
float distanceSq(const glm::vec2 &p1, const glm::vec2 &p2);

/**
 * Color constants for easier use
 */
const vec4 kWhite(1.0f, 1.0f, 1.0f, 1.0f);
const vec4 kBlack(0.0f, 0.0f, 0.0f, 1.0f);
const vec4 kRed(1.0f, 0.0f, 0.0f, 1.0f);
const vec4 kGreen(0.0f, 1.0f, 0.0f, 1.0f);
const vec4 kBlue(0.0f, 0.0f, 1.0f, 1.0f);
const vec4 kYellow(1.0f, 1.0f, 0.0f, 1.0f);
}  // namespace glm

#endif  // _LIBGL2D_PHYSICS_MATH_H_