#include "texture.h"

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace omega {

Texture::Texture(uint32_t width, uint32_t height, GLenum min_filter, GLenum mag_filter) : id_(0), width_(width), height_(height) {
	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_2D, id_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);    // if rendered smaller, use giver filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);    // if rendered larger, use given filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // continue closest color to edge
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	Load(nullptr);
	Unbind();
}

Texture::~Texture() {
	glDeleteTextures(1, &id_);
}

void Texture::Bind(GLuint slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);  // which slot the next texture will use
	glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::Unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Load(uint32_t *pixels) {
	glBindTexture(GL_TEXTURE_2D, id_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	Unbind();
}

sptr<uint32_t[]> Texture::GetPixels() {
	auto pixels = create_sptr<uint32_t[]>(width_ * height_);

	glBindTexture(GL_TEXTURE_2D, id_);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.get());
	glBindTexture(GL_TEXTURE_2D, 0);
	return pixels;
}

}  // namespace omega
