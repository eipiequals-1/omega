#include "shape_renderer.hpp"

#include <string>

#include "omega/gfx/gl.hpp"
#include "omega/gfx/shaders/sr.hpp"

namespace omega::gfx {

ShapeRenderer::ShapeRenderer() : view_proj_matrix_name("u_ViewProjMatrix") {
    // initialize numerical data
    triangles_renderered = 0;
    color = math::vec4(1.0f);
    // create shaders
#ifdef EMSCRIPTEN
    triangle_shader = create_uptr<Shader>(shaders::sr_vert_wasm,
                                          shaders::sr_frag_wasm);
#else
    triangle_shader = create_uptr<Shader>(shaders::sr_vert, shaders::sr_frag);
#endif
    // create vertex buffer
    triangle_vbo = create_uptr<VertexBuffer>(
        sizeof(f32) * num_triangles *
        num_vertices_per_triangle * num_attributes);

    // create vertex buffer layout
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2);
    layout.push(GL_FLOAT, 4);
    // create vertex array
    triangle_vao = create_uptr<VertexArray>();
    triangle_vao->add_buffer(*triangle_vbo, layout);
}

void ShapeRenderer::begin() {
    triangles_renderered = 0;
}

void ShapeRenderer::end() {
    triangle_vao->bind();
    triangle_vbo->bind();
    triangle_shader->bind();
    draw_arrays(GL_TRIANGLES, 0,
                 triangles_renderered * num_vertices_per_triangle);
    // unbind all objects
    VertexArray::unbind();
    VertexBuffer::unbind();
    Shader::unbind();
}

void ShapeRenderer::rect(const math::rectf &rect) {
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

void ShapeRenderer::rect(const math::rectf &rect, f32 rotation) {
    math::vec2 center = rect.center();
    // center rect around origin/center
    math::vec2 points[4] = {};
    points[0] = math::vec2(rect.x, rect.y) - center;
    points[1] = math::vec2(rect.x + rect.w, rect.y) - center;
    points[2] = math::vec2(rect.x + rect.w, rect.y + rect.h) - center;
    points[3] = math::vec2(rect.x, rect.y + rect.h) - center;

    rotation = math::radians(rotation);
    f32 s = math::sin(rotation);
    f32 c = math::cos(rotation);
    for (size_t i = 0; i < 4; ++i) {
        math::vec2 &point = points[i];
        math::vec2 point_old = point;
        point.x = point_old.x * c - point_old.y * s;
        point.y = point_old.y * c + point_old.x * s;
        // revert back to original center
        point += center;
    }
    triangle(points[0], points[1], points[2]);
    triangle(points[2], points[3], points[0]);
}

void ShapeRenderer::triangle(f32 x1, f32 y1,
                             f32 x2, f32 y2,
                             f32 x3, f32 y3) {
    if (triangles_renderered == num_triangles) {
        end();
        begin();
    }

    ShapeVertex v1, v2, v3;
    v1 = {{x1, y1}, color};
    v2 = {{x2, y2}, color};
    v3 = {{x3, y3}, color};
    
    ShapeTriangle triangle = {v1, v2, v3};
    triangle_vbo->bind();
    triangle_vbo->sub_data(
        triangles_renderered * sizeof(ShapeTriangle),
        sizeof(ShapeTriangle),
        triangle.data());
    triangles_renderered++;
}

void ShapeRenderer::triangle(const math::vec2 &p1,
                             const math::vec2 &p2,
                             const math::vec2 &p3) {
    triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
}

void ShapeRenderer::circle(const math::vec2 &center,
                           f32 radius,
                           uint32_t segments) {
    // estimate number of triangles
    f32 angle_incr = math::pi<f32>() * 2 / segments;
    math::vec2 p2, p3;
    f32 s = 0.0f, c = 1.0f;
    for (uint32_t i = 0; i < segments; i++) {
        p2.x = radius * c + center.x;
        p2.y = radius * s + center.y;
        c = math::cos(angle_incr * (i + 1));
        s = math::sin(angle_incr * (i + 1));
        p3.x = radius * c + center.x;
        p3.y = radius * s + center.y;
        triangle(center, p2, p3);
    }
}

void ShapeRenderer::line(const math::vec2 &p1,
                         const math::vec2 &p2,
                         f32 thickness) {
    math::vec2 slope = p2 - p1;
    math::vec2 perpendicular = math::vec2(-slope.y, slope.x);
    math::vec2 norm_perp = math::normalize(perpendicular);
    math::vec2 offset = norm_perp * thickness / 2.0f;
    // render like rotated rectangle
    math::vec2 r1, r2, r3, r4;
    r1 = p1 - offset; // bottom left
    r2 = p2 - offset; // bottom right
    r3 = p2 + offset; // top right
    r4 = p1 + offset; // top left

    triangle(r1, r2, r3);
    triangle(r3, r4, r1);
}

void ShapeRenderer::line(f32 x1, f32 y1,
                         f32 x2, f32 y2,
                         f32 thickness) {
    line(math::vec2(x1, y1), math::vec2(x2, y2), thickness);
}

} // namespace omega::gfx
