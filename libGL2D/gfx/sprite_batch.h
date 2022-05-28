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

namespace libgl {

struct Vertex {
	float position[2];
	float color[4];
	float texCoords[2];
	float tex_id;
	float rotation;
	float center_of_rot[2];
};

using Quad = std::array<Vertex, 4>;

class SpriteBatch {
   public:
	SpriteBatch();
	virtual ~SpriteBatch();

	virtual void SetViewProjectionMatrix(const glm::mat4 &projection) {
		sprite_shader_->Bind();
		sprite_shader_->SetUniformMat4f("u_ViewProjMatrix", projection);
		sprite_shader_->Unbind();
	}

	virtual void BeginRender();
	virtual void EndRender();

	virtual void RenderTexture(const Texture *texture, const float x, const float y, const glm::vec4 &color = glm::vec4(1.0f));
	virtual void RenderTexture(const Texture *texture, const float x, const float y, const float w, const float h, const glm::vec4 &color = glm::vec4(1.0f));

	/**
	 * draw the given part of the texture to the destination
	 * @param texture the texture to draw
	 * @param src subrectangle of texture to draw in pixel units
	 * @param dest the model matrix of the object
	 * @param color tint of the texture
	 */
	virtual void RenderTexture(const Texture *texture, glm::rect src, const glm::rect &dest, const glm::vec4 &color = glm::vec4(1.0f));

	/**
	 * draw the given part of the texture to the destination
	 * @param texture the texture to draw
	 * @param src subrectangle of texture to draw in pixel units
	 * @param dest the model matrix of the object
	 * @param rotation in degrees counterclockwise
	 * @param center center of rotation in world coordinates
	 * @param color tint of the texture
	 */
	virtual void RenderTexture(const Texture *texture, glm::rect src, const glm::rect &dest, float rotation, const glm::vec2 &center, const glm::vec4 &color = glm::vec4(1.0f));

   protected:
	Uptr<Shader> sprite_shader_;
	Uptr<VertexBuffer> vbo_;
	Uptr<VertexArray> vao_;
	Uptr<IndexBuffer> ibo_;
	// buffer constants
	static constexpr uint32_t kQuadCapacity = 1500;
	static constexpr uint32_t kIndexBufferCapacity = kQuadCapacity * 6;
	static constexpr uint32_t kVertexBufferCapacity = kQuadCapacity * 4;
	static constexpr uint32_t kVertexCount = 12;
	static constexpr uint32_t kIndexCount = 6;
	// texture data
	static constexpr uint32_t kMaxTextures = 32;
	std::array<uint32_t, kMaxTextures> texture_binds_;
	std::array<const Texture *, kMaxTextures> textures_to_render_;

	// render attributes
	uint32_t quads_rendered_;
	uint32_t tex_bind_slot_;
};

}  // namespace libgl

#endif  // _LIBGL2D_GFX_SPRITEBATCH_H_