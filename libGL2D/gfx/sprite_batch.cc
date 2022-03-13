#include "sprite_batch.h"

#include <GL/gl.h>

#include <iostream>
#include <memory>

namespace libGL2D {

Quad CreateQuad(float x, float y, float w, float h, float texId, const glm::vec4 &color) {
	Vertex v0 = {{x, y, 0.0f}, {color.r, color.g, color.b, color.a}, {0.0f, 0.0f}, texId};          // bottom left
	Vertex v1 = {{x + w, y, 0.0f}, {color.r, color.g, color.b, color.a}, {1.0f, 0.0f}, texId};      // bottom right
	Vertex v2 = {{x + w, y + h, 0.0f}, {color.r, color.g, color.b, color.a}, {1.0f, 1.0f}, texId};  // top right
	Vertex v3 = {{x, y + h, 0.0f}, {color.r, color.g, color.b, color.a}, {0.0f, 1.0f}, texId};      // top left
	return {v0, v1, v2, v3};
}

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
	vbo_ = std::make_unique<VertexBuffer>(kVertexBufferCapacity * kVertexCount);
	VertexBufferLayout layout;
	layout.Push(GL_FLOAT, 3);
	layout.Push(GL_FLOAT, 4);
	layout.Push(GL_FLOAT, 2);
	layout.Push(GL_FLOAT, 1);
	vao_->AddBuffer(*vbo_, layout);

	texture_binds_.reserve(kMaxTextures);
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
	RenderTexture(texture, x, y, texture->GetWidth(), texture->GetHeight(), color);
}

void SpriteBatch::RenderTexture(const Texture *texture, const float x, const float y, const float w, const float h, const glm::vec4 &color) {
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(x + w / 2.0f, y + h / 2.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), {w, h, 1.0f});
	// set tex coords
	glm::rect tex_coords(0.0f, 0.0f, texture->GetWidth(), texture->GetHeight());
	RenderTexture(texture, tex_coords, transform, color);
}

void SpriteBatch::RenderTexture(const Texture *texture, const float x, const float y, const float w, const float h, const float rotation, const glm::vec4 &color) {
	// shift transform by half size
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), {x + w / 2.0f, y + h / 2.0f, 0.0f}) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), {w, h, 1.0f});
	glm::rect tex_coords(0.0f, 0.0f, texture->GetWidth(), texture->GetHeight());
	RenderTexture(texture, tex_coords, transform, color);
}

void SpriteBatch::RenderTexture(const Texture *texture, glm::rect src, const glm::mat4 &transform, const glm::vec4 &color) {
	if (quads_rendered_ == kQuadCapacity || tex_bind_slot_ == kMaxTextures) {
		EndRender();
		BeginRender();
	}
	float tex_id = tex_bind_slot_;

	// normalize src rect
	src.x = src.x / texture->GetWidth();
	src.y = src.y / texture->GetHeight();
	src.w = src.w / texture->GetWidth();
	src.h = src.h / texture->GetHeight();

	glm::vec3 p = transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
	Vertex v0 = {{p.x, p.y, p.z}, {color.r, color.g, color.b, color.a}, {src.x, src.y}, tex_id};
	p = transform * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
	Vertex v1 = {{p.x, p.y, p.z}, {color.r, color.g, color.b, color.a}, {src.x + src.w, src.y}, tex_id};
	p = transform * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
	Vertex v2 = {{p.x, p.y, p.z}, {color.r, color.g, color.b, color.a}, {src.x + src.w, src.y + src.h}, tex_id};
	p = transform * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);
	Vertex v3 = {{p.x, p.y, p.z}, {color.r, color.g, color.b, color.a}, {src.x, src.y + src.h}, tex_id};

	Quad q = {v0, v1, v2, v3};
	auto quad = q.data();

	texture->Bind(tex_bind_slot_);
	tex_bind_slot_++;

	vbo_->Bind();
	vbo_->SubData(sizeof(Quad) * quads_rendered_, sizeof(Quad), quad);
	quads_rendered_++;
}

void SpriteBatch::RenderTexture(const Texture *texture, const float x, const float y, const float w, const float h, const glm::vec2 &center_of_rotation, const float rotation, const glm::vec4 &color) {
	// scale
	// rotate about point
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), {x + w / 2.0f, y + h / 2.0f, 0.0f});
	transform = transform * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f});
	transform = transform * glm::translate(glm::mat4(1.0f), {center_of_rotation.x - w / 2.0f, center_of_rotation.y - h / 2.0f, 0.0f});
	transform = transform * glm::scale(glm::mat4(1.0f), {w, h, 1.0f});
	// translate to center pos
	glm::rect tex_coords(0.0f, 0.0f, 1.0f, 1.0f);
	RenderTexture(texture, tex_coords, transform, color);
}

void SpriteBatch::RenderTexture(const Texture *texture, const glm::rect &src, const glm::rect &dest, const glm::vec4 &color) {
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(dest.x + dest.w / 2.0f, dest.y + dest.h / 2.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), {dest.w, dest.h, 1.0f});
	RenderTexture(texture, src, transform, color);
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

}  // namespace libGL2D
