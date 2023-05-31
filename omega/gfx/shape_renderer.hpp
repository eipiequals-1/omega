#ifndef OMEGA_GFX_SHAPERENDERER_HPP
#define OMEGA_GFX_SHAPERENDERER_HPP

#include <array>
#include <cstdint>
#include <string>

#include "omega/gfx/gl.hpp"
#include "omega/gfx/shader.hpp"
#include "omega/gfx/vertex_array.hpp"
#include "omega/gfx/vertex_buffer.hpp"
#include "omega/gfx/vertex_buffer_layout.hpp"
#include "omega/util/math.hpp"
#include "omega/util/std.hpp"

namespace omega::gfx {

using namespace omega::util;

/**
 * ShapeRenderer renders rectangles, circles, lines, etc.
 * Uses batch rendering for better results
 * Example:
 *     shape_renderer.begin();
 *     shape_renderer.circle(glm::vec2(50.0f, 50.0f), 50.0f);
 *     shape_renderer.color(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
 *     shape_renderer.rect(glm::rectf(0.0f, 0.0f, 100.0f, 100.0f));
 *     shape_renderer.end();
 */
class ShapeRenderer {
  public:
    ShapeRenderer();
   ~ShapeRenderer() = default;

    /**
     * Begins the rendering process.
     */
    void begin();

    /**
     * Ends the rendering process and sends all the triangles to the shader
     * and draws it on screen.
     */
    void end();

    /**
     * Sets the view projection matrix, typically represented by a camera
     * Must be called before rendering:
     * i.e. ShapeRenderer::end();
     * @param mat the view projection matrix
     */
    void set_view_projection_matrix(const glm::mat4 &mat) {
        triangle_shader->bind();
        triangle_shader->set_uniform_mat4f(view_proj_matrix_name, mat);
        triangle_shader->unbind();
    }

    /**
     * Set the next render call's color
     * @param co color
     */
    void color(const glm::vec4 &co) {
        color(co.r, co.g, co.b, co.a);
    }

    /**
     * Set the next render call's color
     * @param co color
     */
    void color(const glm::vec3 &co) {
        color(co.r, co.g, co.b, 1.0f);
    }

    /**
     * Set the next render call's color
     * @param r red
     * @param g green
     * @param b blue
     */
    void color(f32 r, f32 g, f32 b) {
        color(r, g, b, 1.0f);
    }

    /**
     * Set the next render call's color
     * @param r red
     * @param g green
     * @param b blue
     * @param a alpha
     */
    void color(f32 r, f32 g, f32 b, f32 a) {
        current_color.r = r;
        current_color.g = g;
        current_color.b = b;
        current_color.a = a;
    }

    /**
     * Renders a rectangle with the current ShapeRenderer::color
     * @param rect rect in world space coords
     */
    void rect(const glm::rectf &rect);

    /**
     * Renders a rotated rectangle with the current ShapeRenderer::color
     * @param rect rect in world space coords
     * @param rotation in trigonometric direction & degrees
     */
    void rect(const glm::rectf &rect, f32 rotation);

    /**
     * Renders a triangle with the given points
     * and the current ShapeRenderer::color
     * @param p1 point 1
     * @param p2 point 2
     * @param p3 point 3
     */
    void triangle(const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3);

    /**
     * Renders a triangle with the given points
     * and the current ShapeRenderer::color
     */
    void triangle(f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3);

    /**
     * Renders a Circle by approximating the number of triangle segments to draw
     * based off of radius
     * @param center the center of the circle
     * @param radius the radius
     */
    void circle(const glm::vec2 &center, f32 radius, u32 segments);

    /**
     * Renders a line with the specified points and thickness
     * Uses perpendicular slopes to draw line
     * The line is essentially a rotated rectangle
     * @param p1 point 1
     * @param p2 point 2
     * @param thickness width of line
     */
    void line(const glm::vec2 &p1, const glm::vec2 &p2, f32 thickness = 1.0f);

    /**
     * Renders a line in the same way as
     *
     * ShapeRenderer::line(const glm::vec2 &p1,
     *                     const glm::vec2 &p2,
     *                     f32 thickness);
     */
    void line(f32 x1, f32 y1, f32 x2, f32 y2, f32 thickness = 1.0f);

  private:
    //
    static const u32 num_triangles = 1000;
    static const u32 num_vertices_per_triangle = 3;
    static const u32 num_attributes = 6;
    const std::string view_proj_matrix_name;

    // OpenGL objects
    uptr<Shader> triangle_shader = nullptr;
    uptr<VertexBuffer> triangle_vbo = nullptr;
    uptr<VertexArray> triangle_vao = nullptr;

    u32 triangles_renderered = 0;
    glm::vec4 current_color{1.0f}; // tracks current color

    /**
     * CPU representation of each Vertex for the ShapeRenderer with:
     * position,
     * color
     */
    struct ShapeVertex {
        glm::vec2 pos;
        glm::vec4 color;
    };

    // Represent the shape in 3 vertices
    using ShapeTriangle = std::array<ShapeVertex, 3>;
};
} // namespace omega::gfx

#endif // OMEGA_GFX_SHAPERENDERER_HPP
