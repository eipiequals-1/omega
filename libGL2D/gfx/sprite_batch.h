#ifndef _LIBGL2D_GFX_SPRITEBATCH_H_
#define _LIBGL2D_GFX_SPRITEBATCH_H_

#include <GL/gl.h>

#include <cstring>
#include <memory>
#include <vector>

#include "libGL2D/core/using.h"
#include "libGL2D/gfx/index_buffer.h"
#include "libGL2D/gfx/shader.h"
#include "libGL2D/gfx/texture/texture.h"
#include "libGL2D/gfx/vertex_array.h"
#include "libGL2D/gfx/vertex_buffer.h"
#include "libGL2D/gfx/vertex_buffer_layout.h"
#include "libGL2D/physics/math.h"

namespace libGL2D {

struct Vertex {
	float position[3];
	float color[4];
	float texCoords[2];
	float texId;
};

using Quad = std::array<Vertex, 4>;

Quad CreateQuad(float x, float y, float w, float h, float texId, const glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

class SpriteBatch {
   public:
	SpriteBatch();
	virtual ~SpriteBatch();

	virtual void SetViewProjectionMatrix(const glm::mat4 &projection) {
		sprite_shader_->Bind();
		sprite_shader_->SetUniformMat4f("u_ViewProjMatrix", projection);
	}

	virtual void BeginRender();

	virtual void EndRender();

	virtual void RenderTexture(const Texture *texture, const float x, const float y, const glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	virtual void RenderTexture(const Texture *texture, const float x, const float y, const float w, const float h, const glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	virtual void RenderTexture(const Texture *texture, const float x, const float y, const float w, const float h, float rotation, const glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	/**
	 * RenderTexture Quad rotated around an arbitrary point
	 * @param texture pointer to texture
	 * @param x left
	 * @param y bottom
	 * @param w width
	 * @param h height
	 * @param center_of_rotation point in quad
	 * @param rotation counter clockwise rotation in degrees
	 * @param color tint of quad
	 */
	virtual void RenderTexture(const Texture *texture, const float x, const float y, const float w, const float h, const glm::vec2 &center_of_rotation, const float rotation, const glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	/**
	 * Base RenderTexture Function called on every quad RenderTexture
	 * @param texture the texture to draw
	 * @param src subrectangle of texture to draw in pixel units
	 * @param transform the model matrix of the object
	 * @param color tint of the texture
	 */
	virtual void RenderTexture(const Texture *texture, glm::rect src, const glm::mat4 &transform, const glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	// RenderTexture parts of a texture
	virtual void RenderTexture(const Texture *texture, const glm::rect &src, const glm::rect &dest, const glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

   private:
	Uptr<Shader> sprite_shader_;
	Uptr<VertexBuffer> vbo_;
	Uptr<VertexArray> vao_;
	Uptr<IndexBuffer> ibo_;

	static constexpr uint32_t kQuadCapacity = 1000;
	static constexpr uint32_t kIndexBufferCapacity = 1000 * 6;
	static constexpr uint32_t kVertexBufferCapacity = 1000 * 4;
	static constexpr uint32_t kVertexCount = 10;
	static constexpr uint32_t kIndexCount = 6;

	static constexpr uint32_t kMaxTextures = 32;
	std::vector<int> texture_binds_;
	std::vector<const Texture *> textures_to_render_;

	uint32_t quads_rendered_;
	uint32_t tex_bind_slot_;
};

}  // namespace libGL2D

#endif  // _LIBGL2D_GFX_SPRITEBATCH_H_