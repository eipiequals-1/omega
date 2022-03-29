#include "sprite_batch.h"

#include <GL/gl.h>

#include <algorithm>
#include <iostream>
#include <memory>

namespace libgl {

SpriteBatch::SpriteBatch() : quads_rendered_(0), tex_bind_slot_(0) {
	// indices will never change so set them now
	uint32_t indices[kIndexBufferCapacity];
	uint32_t offset = 0;
	for (size_t i = 0; i < kIndexBufferCapacity; i += 6) {
		// triangle 1
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;
		// triangle 2
		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}
	ibo_ = std::make_unique<IndexBuffer>(indices, kIndexBufferCapacity);

	sprite_shader_ = std::make_unique<Shader>("./res/shader/sprite.shader");
	vao_ = std::make_unique<VertexArray>();
	vbo_ = std::make_unique<VertexBuffer>(kVertexBufferCapacity * kVertexCount * sizeof(float));
	VertexBufferLayout layout;
	layout.Push(GL_FLOAT, 3);
	layout.Push(GL_FLOAT, 4);
	layout.Push(GL_FLOAT, 2);
	layout.Push(GL_FLOAT, 1);
	vao_->AddBuffer(*vbo_, layout);

	for (uint32_t i = 0; i < kMaxTextures; ++i) {
		texture_binds_[i] = i;
	}
}

SpriteBatch::~SpriteBatch() {
}

void SpriteBatch::BeginRender() {
	quads_rendered_ = 0;
	tex_bind_slot_ = 0;
}

void SpriteBatch::RenderTexture(const Texture *texture, const float x, const float y, const glm::vec4 &color) {
	RenderTexture(texture, x, y, texture->get_width(), texture->get_height(), color);
}

void SpriteBatch::RenderTexture(const Texture *texture, const float x, const float y, const float w, const float h, const glm::vec4 &color) {
	// set tex coords
	glm::rect tex_coords(0.0f, 0.0f, texture->get_width(), texture->get_height());
	RenderTexture(texture, tex_coords, glm::rect(x, y, w, h), color);
}

void SpriteBatch::RenderTexture(const Texture *texture, glm::rect src, const glm::rect &dest, const glm::vec4 &color) {
	if (quads_rendered_ == kQuadCapacity || tex_bind_slot_ == kMaxTextures) {
		EndRender();
		BeginRender();
	}
	float tex_id = tex_bind_slot_;
	// check if texture has been used in this batch
	auto found_itr = std::find(textures_to_render_.begin(), textures_to_render_.end(), texture);
	if (found_itr != textures_to_render_.end()) {
		tex_id = found_itr - textures_to_render_.begin();
		// std::cout << "already_bound\n";
	} else {
		// add the texture to the to render vector and bind
		textures_to_render_[tex_bind_slot_] = texture;
		texture->Bind(tex_bind_slot_);
		tex_bind_slot_++;
		// std::cout << "not already_bound\n";
	}
	// normalize src rect
	src.x = src.x / texture->get_width();
	src.y = src.y / texture->get_height();
	src.w = src.w / texture->get_width();
	src.h = src.h / texture->get_height();
	const float z = 0.0f;
	Vertex v0 = {{dest.x, dest.y, z}, {color.r, color.g, color.b, color.a}, {src.x, src.y}, tex_id};
	Vertex v1 = {{dest.x + dest.w, dest.y, z}, {color.r, color.g, color.b, color.a}, {src.x + src.w, src.y}, tex_id};
	Vertex v2 = {{dest.x + dest.w, dest.y + dest.h, z}, {color.r, color.g, color.b, color.a}, {src.x + src.w, src.y + src.h}, tex_id};
	Vertex v3 = {{dest.x, dest.y + dest.h, z}, {color.r, color.g, color.b, color.a}, {src.x, src.y + src.h}, tex_id};

	Quad q = {v0, v1, v2, v3};
	auto quad = q.data();

	vbo_->Bind();
	vbo_->SubData(sizeof(Quad) * quads_rendered_, sizeof(Quad), quad);
	quads_rendered_++;
}

void SpriteBatch::EndRender() {
	const std::string kTextureUniformKey = "u_Textures";

	sprite_shader_->Bind();
	sprite_shader_->SetUniform1iv(kTextureUniformKey, texture_binds_.data(), kMaxTextures);
	vao_->Bind();
	ibo_->Bind();
	glDrawElements(GL_TRIANGLES, quads_rendered_ * kIndexCount, GL_UNSIGNED_INT, nullptr);
	vao_->Unbind();
	ibo_->Unbind();
	sprite_shader_->Unbind();
}

}  // namespace libgl
