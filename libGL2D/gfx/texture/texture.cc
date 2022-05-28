#include "texture.h"

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

namespace libgl {

Texture::Texture(const std::string& filepath, GLenum min_filter, GLenum mag_filter) : id_(0), min_filter_(min_filter), mag_filter_(mag_filter), pixels_(nullptr), width_(0), height_(0) {
	SDL_Surface* surf = IMG_Load(filepath.c_str());
	if (surf == nullptr) {
		libgl::Log("IMG error: Error loading '", filepath, "': ", IMG_GetError());
		return;
	}
	width_ = surf->w;
	height_ = surf->h;
	pixels_ = (uint32_t*)surf->pixels;
	Load();
}

Texture::Texture(uint32_t width, uint32_t height, GLenum min_filter, GLenum mag_filter) : id_(0), min_filter_(min_filter), mag_filter_(mag_filter), pixels_(nullptr), width_(width), height_(height) {
	Load();
}

Texture::~Texture() {
	glDeleteTextures(1, &id_);
	delete[] pixels_;
	pixels_ = nullptr;
}

void Texture::Bind(GLuint slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);  // which slot the next texture will use
	glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::Unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Load() {
	glGenTextures(1, &id_);
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter_);   // if rendered smaller, use giver filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter_);   // if rendered larger, use given filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // continue closest color to edge
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels_);
	Unbind();
}
}  // namespace libgl
