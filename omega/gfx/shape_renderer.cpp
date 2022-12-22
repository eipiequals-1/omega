#include "shape_renderer.h"

#include <string>

namespace omega::gfx {

ShapeRenderer::ShapeRenderer() : kViewProjMatrixName("u_ViewProjMatrix") {
    // initialize numerical data
    triangles_renderered = 0;
    current_color = glm::vec4(1.0f);
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
    triangle_shader = create_uptr<Shader>(std::string(vertex), std::string(fragment));
    // create vertex buffer
    triangle_vbo = create_uptr<VertexBuffer>(sizeof(float) * kNumTriangles * kNumVerticesPerTriangle * kNumAttributes);
    // create vertex array
    triangle_vao = create_uptr<VertexArray>();
    // create vertex buffer layout
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2);
    layout.push(GL_FLOAT, 4);
    triangle_vao->add_buffer(*triangle_vbo, layout);
}

ShapeRenderer::~ShapeRenderer() {
}

void ShapeRenderer::begin() {
    triangles_renderered = 0;
}

void ShapeRenderer::end() {
    triangle_shader->bind();
    triangle_vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, triangles_renderered * kNumVerticesPerTriangle);
    // unbind all objects
    VertexArray::unbind();
    Shader::unbind();
}

void ShapeRenderer::rect(const glm::rectf &rect) {
    triangle(
        rect.x, rect.y,                  // bottom left
        rect.x + rect.w, rect.y,         // bottom right
        rect.x + rect.w, rect.y + rect.h // top right
    );
    triangle(
        rect.x, rect.y,                  // bottom left
        rect.x, rect.y + rect.h,         // top left
        rect.x + rect.w, rect.y + rect.h // top right
    );
}

void ShapeRenderer::rect(const glm::rectf &rect, float rotation) {
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
    triangle(points[0], points[1], points[2]);
    triangle(points[2], points[3], points[0]);
}

void ShapeRenderer::triangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    if (triangles_renderered == kNumTriangles) {
        end();
        begin();
    }

    ShapeVertex v1, v2, v3;
    v1 = {{x1, y1}, {current_color.r, current_color.g, current_color.b, current_color.a}};
    v2 = {{x2, y2}, {current_color.r, current_color.g, current_color.b, current_color.a}};
    v3 = {{x3, y3}, {current_color.r, current_color.g, current_color.b, current_color.a}};
    ShapeTriangle triangle = {v1, v2, v3};
    triangle_vbo->bind();
    triangle_vbo->sub_data(triangles_renderered * sizeof(ShapeTriangle), sizeof(ShapeTriangle), triangle.data());
    triangles_renderered++;
}

void ShapeRenderer::triangle(const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3) {
    triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
}

void ShapeRenderer::circle(const glm::vec2 &center, float radius, uint32_t segments) {
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
        triangle(center, p2, p3);
    }
}

void ShapeRenderer::line(const glm::vec2 &p1, const glm::vec2 &p2, float thickness) {
    glm::vec2 slope = p2 - p1;
    glm::vec2 perpendicular = glm::vec2(-slope.y, slope.x);
    glm::vec2 norm_perp = glm::normalize(perpendicular);
    glm::vec2 offset = norm_perp * thickness / 2.0f;
    // render like rotated rectangle
    glm::vec2 r1, r2, r3, r4;
    r1 = p1 - offset; // bottom left
    r2 = p2 - offset; // bottom right
    r3 = p2 + offset; // top right
    r4 = p1 + offset; // top left

    triangle(r1, r2, r3);
    triangle(r3, r4, r1);
}

void ShapeRenderer::line(float x1, float y1, float x2, float y2, float thickness) {
    line(glm::vec2(x1, y1), glm::vec2(x2, y2), thickness);
}

} // namespace omega::gfx