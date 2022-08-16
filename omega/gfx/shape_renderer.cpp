#include "shape_renderer.h"

#include <string>

namespace omega {

ShapeRenderer::ShapeRenderer() : kViewProjMatrixName("u_ViewProjMatrix") {
	// initialize numerical data
	triangles_renderered_ = 0;
	color_ = glm::vec4(1.0f);
	// create shaders
	char vertex[] = R"glsl(
        #version 450

        layout(location=0) in vec2 a_Coord;
        layout(location=1) in vec4 a_Color;

        layout(location=0) out vec4 v_Color;

        uniform mat4 u_ViewProjMatrix;

        void main() {
            gl_Position = u_ViewProjMatrix * vec4(a_Coord.x, a_Coord.y, 0.0, 1.0);
            v_Color = a_Color;
        }
    )glsl";

	char fragment[] = R"glsl(
        #version 450

        layout(location=0) in vec4 v_Color;
        out vec4 color;

        void main() {
            color = v_Color;
        }
    )glsl";
	triangle_shader_ = CreateUptr<Shader>(std::string(vertex), std::string(fragment));
	// create vertex buffer
	triangle_vbo_ = CreateUptr<VertexBuffer>(sizeof(float) * kNumTriangles * kNumVerticesPerTriangle * kNumAttributes);
	// create vertex array
	triangle_vao_ = CreateUptr<VertexArray>();
	// create vertex buffer layout
	VertexBufferLayout layout;
	layout.Push(GL_FLOAT, 2);
	layout.Push(GL_FLOAT, 4);
	triangle_vao_->AddBuffer(*triangle_vbo_, layout);
}

ShapeRenderer::~ShapeRenderer() {
}

void ShapeRenderer::Begin() {
	triangles_renderered_ = 0;
}

void ShapeRenderer::End() {
	triangle_shader_->Bind();
	triangle_vao_->Bind();
	glDrawArrays(GL_TRIANGLES, 0, triangles_renderered_ * kNumVerticesPerTriangle);
	// unbind all objects
	triangle_shader_->Unbind();
	triangle_vao_->Unbind();
}

void ShapeRenderer::Rect(const glm::rectf &rect) {
	Triangle(
	    rect.x, rect.y,                   // bottom left
	    rect.x + rect.w, rect.y,          // bottom right
	    rect.x + rect.w, rect.y + rect.h  // top right
	);
	Triangle(
	    rect.x, rect.y,                   // bottom left
	    rect.x, rect.y + rect.h,          // top left
	    rect.x + rect.w, rect.y + rect.h  // top right
	);
}

void ShapeRenderer::Rect(const glm::rectf &rect, float rotation) {
	glm::vec2 center = rect.center();
	// center rect around origin/center
	glm::vec2 points[4] = {};
	points[0] = glm::vec2(rect.x, rect.y) - center;
	points[1] = glm::vec2(rect.x + rect.w, rect.y) - center;
	points[2] = glm::vec2(rect.x + rect.w, rect.y + rect.h) - center;
	points[3] = glm::vec2(rect.x, rect.y + rect.h) - center;

	rotation = glm::radians(rotation);
	float s = glm::sin(rotation);
	float c = glm::cos(rotation);
	for (size_t i = 0; i < 4; ++i) {
		glm::vec2 &point = points[i];
		glm::vec2 point_old = point;
		point.x = point_old.x * c - point_old.y * s;
		point.y = point_old.y * c + point_old.x * s;
		// revert back to original center
		point += center;
	}
	Triangle(points[0], points[1], points[2]);
	Triangle(points[2], points[3], points[0]);
}

void ShapeRenderer::Triangle(float x1, float y1, float x2, float y2, float x3, float y3) {
	if (triangles_renderered_ == kNumTriangles) {
		End();
		Begin();
	}

	ShapeVertex v1, v2, v3;
	v1 = {{x1, y1}, {color_.r, color_.g, color_.b, color_.a}};
	v2 = {{x2, y2}, {color_.r, color_.g, color_.b, color_.a}};
	v3 = {{x3, y3}, {color_.r, color_.g, color_.b, color_.a}};
	ShapeTriangle triangle = {v1, v2, v3};
	triangle_vbo_->Bind();
	triangle_vbo_->SubData(triangles_renderered_ * sizeof(ShapeTriangle), sizeof(ShapeTriangle), triangle.data());
	triangles_renderered_++;
}

void ShapeRenderer::Triangle(const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3) {
	Triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
}

void ShapeRenderer::Circle(const glm::vec2 &center, float radius, uint32_t segments) {
	// estimate number of triangles
	float angle_incr = glm::pi<float>() * 2 / segments;
	glm::vec2 p2, p3;
	float s = 0.0f, c = 1.0f;
	for (uint32_t i = 0; i < segments; i++) {
		p2.x = radius * c + center.x;
		p2.y = radius * s + center.y;
		c = glm::cos(angle_incr * (i + 1));
		s = glm::sin(angle_incr * (i + 1));
		p3.x = radius * c + center.x;
		p3.y = radius * s + center.y;
		Triangle(center, p2, p3);
	}
}

void ShapeRenderer::Line(const glm::vec2 &p1, const glm::vec2 &p2, float thickness) {
	glm::vec2 slope = p2 - p1;
	glm::vec2 perpendicular = glm::vec2(-slope.y, slope.x);
	glm::vec2 norm_perp = glm::normalize(perpendicular);
	glm::vec2 offset = norm_perp * thickness / 2.0f;
	// render like rotated rectangle
	glm::vec2 r1, r2, r3, r4;
	r1 = p1 - offset;  // bottom left
	r2 = p2 - offset;  // bottom right
	r3 = p2 + offset;  // top right
	r4 = p1 + offset;  // top left

	Triangle(r1, r2, r3);
	Triangle(r3, r4, r1);
}

void ShapeRenderer::Line(float x1, float y1, float x2, float y2, float thickness) {
	Line(glm::vec2(x1, y1), glm::vec2(x2, y2), thickness);
}

}  // namespace omega