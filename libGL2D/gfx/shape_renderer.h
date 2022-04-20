#ifndef _LIBGL2D_GFX_SHAPERENDERER_H_
#define _LIBGL2D_GFX_SHAPERENDERER_H_

#include <array>

#include "libGL2D/core/using.h"
#include "libGL2D/gfx/shader.h"
#include "libGL2D/gfx/vertex_array.h"
#include "libGL2D/gfx/vertex_buffer.h"
#include "libGL2D/gfx/vertex_buffer_layout.h"

namespace libgl {

struct ShapeVertex {
	float pos[2];
	float color[4];
};

using ShapeTriangle = std::array<ShapeVertex, 3>;

/**
 * ShapeRenderer renders rectangles, circles, lines, etc.
 * Uses batch rendering for better results
 * Example:
 *     shape_renderer.Begin();
 *     shape_renderer.Circle(glm::vec2(50.0f, 50.0f), 50.0f);
 *     shape_renderer.Color(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
 *     shape_renderer.Rect(glm::rect(0.0f, 0.0f, 100.0f, 100.0f));
 *     shape_renderer.End();
 */
class ShapeRenderer {
   public:
	ShapeRenderer();
	virtual ~ShapeRenderer();

	virtual void Begin();
	virtual void End();
	virtual void SetViewProjectionMatrix(const glm::mat4 &mat) {
		shader_->Bind();
		shader_->SetUniformMat4f(kViewProjMatrixName, mat);
		shader_->Unbind();
	}

	virtual void Color(const glm::vec4 &co) {
		Color(co.r, co.g, co.b, co.a);
	}

	virtual void Color(const glm::vec3 &co) {
		Color(co.r, co.g, co.b, 1.0f);
	}

	virtual void Color(float r, float g, float b) {
		Color(r, g, b, 1.0f);
	}

	virtual void Color(float r, float g, float b, float a) {
		color_.r = r;
		color_.g = g;
		color_.b = b;
		color_.a = a;
	}

	/**
	 * Renders a rectangle with the current ShapeRenderer::color_
	 * @param rect rect in world space coords
	 */
	virtual void Rect(const glm::rect &rect);

	/**
	 * Renders a triangle with the given points
	 * and the current ShapeRenderer::color_
	 * @param p1 point 1
	 * @param p2 point 2
	 * @param p3 point 3
	 */
	virtual void Triangle(const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3);

	/**
	 * Renders a triangle with the given points
	 * and the current ShapeRenderer::color_
	 */
	virtual void Triangle(float x1, float y1, float x2, float y2, float x3, float y3);

	/**
	 * Renders a Circle by approximating the number of triangle segments to draw
	 * based off of radius
	 * @param center the center of the circle
	 * @param radius the radius
	 */
	virtual void Circle(const glm::vec2 &center, float radius);

	/**
	 * Renders a line with the specified points and thickness
	 * Uses perpendicular slopes to draw line
	 * The line is essentially a rotated rectangle
	 * @param p1 point 1
	 * @param p2 point 2
	 * @param thickness width of line
	 */
	virtual void Line(const glm::vec2 &p1, const glm::vec2 &p2, float thickness = 1.0f);

	/**
	 * Renders a line in the same way as
	 *
	 * ShapeRenderer::Line(const glm::vec2 &p1, const glm::vec2 &p2, float thickness)
	 */
	virtual void Line(float x1, float y1, float x2, float y2, float thickness = 1.0f);

   protected:
	static const uint32_t kNumTriangles = 1000;
	static const uint32_t kNumVerticesPerTriangle = 3;
	static const uint32_t kNumAttributes = 6;
	static const uint32_t k;
	const std::string kViewProjMatrixName;

	// OpenGL objects
	Uptr<Shader> shader_;
	Uptr<VertexBuffer> vbo_;
	Uptr<VertexArray> vao_;

	uint32_t triangles_renderered_;
	glm::vec4 color_;  // tracks current color
};
}  // namespace libgl

#endif  // _LIBGL2D_GFX_SHAPERENDERER_H_