#ifndef OMEGA_GFX_SHAPERENDERER_H
#define OMEGA_GFX_SHAPERENDERER_H

#include <array>

#include "omega/gfx/shader.h"
#include "omega/gfx/vertex_array.h"
#include "omega/gfx/vertex_buffer.h"
#include "omega/gfx/vertex_buffer_layout.h"
#include "omega/util/util.h"

namespace omega::gfx {

using namespace omega::util;

/**
 * CPU representation of each Vertex for the ShapeRenderer with:
 * position,
 * color
 */
struct ShapeVertex {
    float pos[2];
    float color[4];
};

// Represent the shape in 3 vertices
using ShapeTriangle = std::array<ShapeVertex, 3>;

/**
 * ShapeRenderer renders rectangles, circles, lines, etc.
 * Uses batch rendering for better results
 * Example:
 *     shape_renderer.Begin();
 *     shape_renderer.Circle(glm::vec2(50.0f, 50.0f), 50.0f);
 *     shape_renderer.Color(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
 *     shape_renderer.Rect(glm::rectf(0.0f, 0.0f, 100.0f, 100.0f));
 *     shape_renderer.End();
 */
class ShapeRenderer {
  public:
    ShapeRenderer(const ShapeRenderer &) = delete;
    ShapeRenderer operator=(const ShapeRenderer &) = delete;
    virtual ~ShapeRenderer();

    static ShapeRenderer &instance() {
        static ShapeRenderer renderer;
        return renderer;
    }

    /**
     * Begins the rendering process.
     */
    virtual void begin();

    /**
     * Ends the rendering process and sends all the triangles to the shader
     * and draws it on screen.
     */
    virtual void end();

    /**
     * Sets the view projection matrix, typically represented by a camera
     * Must be called before rendering:
     * i.e. ShapeRenderer::end();
     * @param mat the view projection matrix
     */
    virtual void set_view_projection_matrix(const glm::mat4 &mat) {
        triangle_shader->bind();
        triangle_shader->set_uniform_mat4f(kViewProjMatrixName, mat);
        triangle_shader->unbind();
    }

    /**
     * Set the next render call's color
     * @param co color
     */
    virtual void color(const glm::vec4 &co) {
        color(co.r, co.g, co.b, co.a);
    }

    /**
     * Set the next render call's color
     * @param co color
     */
    virtual void color(const glm::vec3 &co) {
        color(co.r, co.g, co.b, 1.0f);
    }

    /**
     * Set the next render call's color
     * @param r red
     * @param g green
     * @param b blue
     */
    virtual void color(float r, float g, float b) {
        color(r, g, b, 1.0f);
    }

    /**
     * Set the next render call's color
     * @param r red
     * @param g green
     * @param b blue
     * @param a alpha
     */
    virtual void color(float r, float g, float b, float a) {
        current_color.r = r;
        current_color.g = g;
        current_color.b = b;
        current_color.a = a;
    }

    /**
     * Renders a rectangle with the current ShapeRenderer::color
     * @param rect rect in world space coords
     */
    virtual void rect(const glm::rectf &rect);

    /**
     * Renders a rotated rectangle with the current ShapeRenderer::color
     * @param rect rect in world space coords
     * @param rotation in trigonometric direction & degrees
     */
    virtual void rect(const glm::rectf &rect, float rotation);

    /**
     * Renders a triangle with the given points
     * and the current ShapeRenderer::color
     * @param p1 point 1
     * @param p2 point 2
     * @param p3 point 3
     */
    virtual void triangle(const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3);

    /**
     * Renders a triangle with the given points
     * and the current ShapeRenderer::color
     */
    virtual void triangle(float x1, float y1, float x2, float y2, float x3, float y3);

    /**
     * Renders a Circle by approximating the number of triangle segments to draw
     * based off of radius
     * @param center the center of the circle
     * @param radius the radius
     */
    virtual void circle(const glm::vec2 &center, float radius, uint32_t segments);

    /**
     * Renders a line with the specified points and thickness
     * Uses perpendicular slopes to draw line
     * The line is essentially a rotated rectangle
     * @param p1 point 1
     * @param p2 point 2
     * @param thickness width of line
     */
    virtual void line(const glm::vec2 &p1, const glm::vec2 &p2, float thickness = 1.0f);

    /**
     * Renders a line in the same way as
     *
     * ShapeRenderer::line(const glm::vec2 &p1, const glm::vec2 &p2, float thickness);
     */
    virtual void line(float x1, float y1, float x2, float y2, float thickness = 1.0f);

  protected:
    //
    static const uint32_t kNumTriangles = 1000;
    static const uint32_t kNumVerticesPerTriangle = 3;
    static const uint32_t kNumAttributes = 6;
    const std::string kViewProjMatrixName;

    // OpenGL objects
    uptr<Shader> triangle_shader;
    uptr<VertexBuffer> triangle_vbo;
    uptr<VertexArray> triangle_vao;

    uint32_t triangles_renderered;
    glm::vec4 current_color; // tracks current color

  private:
    ShapeRenderer();
};
} // namespace omega::gfx

#endif // OMEGA_GFX_SHAPERENDERER_H