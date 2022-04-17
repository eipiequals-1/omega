#include "texture.h"

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

namespace libgl {

Texture::Texture(const std::string& filepath, GLenum minFilter, GLenum magFilter) : id(0), filepath(filepath), surf(nullptr), flipped_pixels_(nullptr), width(0), height(0) {
	surf = IMG_Load(filepath.c_str());
	if (surf == nullptr) {
		std::cout << "IMG error: Error loading '" + filepath + "': " + IMG_GetError() << "\n";
		return;
	}
	width = surf->w;
	height = surf->h;
	Load(minFilter, magFilter);
}

Texture::Texture(SDL_Surface* surf, GLenum minFilter, GLenum magFilter) : id(0), surf(surf), flipped_pixels_(nullptr), width(0), height(0) {
	if (surf == nullptr) {
		std::cout << "SDL_Surface error: Invalid Surface (surf = nullptr)\n";
	}
	width = surf->w;
	height = surf->h;
	Load(minFilter, magFilter);
}

Texture::Texture(uint32_t* pixels, uint32_t width, uint32_t height, GLenum minFilter, GLenum magFilter) {
	uint32_t rmask, gmask, bmask, amask;
	if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	} else {
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	}
	SDL_Surface* surf = SDL_CreateRGBSurfaceFrom(pixels, width, height, 32, 4, rmask, gmask, bmask, amask);
	if (surf == nullptr) {
		Log("Unable to create new Texture from pixels");
	}
	width = surf->w;
	height = surf->h;
	Load(minFilter, magFilter);
}

Texture::~Texture() {
	glDeleteTextures(1, &id);
	if (surf != nullptr) SDL_FreeSurface(surf);
	surf = nullptr;
	delete[] flipped_pixels_;
	flipped_pixels_ = nullptr;
}

void Texture::Bind(GLuint slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);  // which slot the next texture will use
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SaveToFile(const std::string& filepath) {
	SDL_SaveBMP(surf, filepath.c_str());
}

void Texture::FlipVertical() {
	// if texture is already flipped
	if (flipped_pixels_ != nullptr) {
		return;
	}
	flipped_pixels_ = new uint32_t[width * height];
	GLuint* sdl_pixels = (GLuint*)surf->pixels;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			GLuint original_pix = sdl_pixels[row * width + col];  // get data in sdl_image

			// evaluate flipped pix idx and pointer
			uint32_t flipped_pix_idx = (height - 1 - row) * width + col;
			GLuint* flipped_pix = &flipped_pixels_[flipped_pix_idx];
			// set flipped pixel to original pix data
			*flipped_pix = original_pix;
		}
	}
}

void Texture::Load(GLenum minFilter, GLenum magFilter) {
	glGenTextures(1, &id);
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);     // if rendered smaller, use linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);     // if rendered larger, use linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // continue closest color to edge
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	bpp = surf->format->BytesPerPixel;
	GLint format;
	// rgba format
	if (bpp == 4) {
		if (surf->format->Rmask == 255) {
			format = GL_RGBA;
		} else {
			format = GL_BGRA;
		}
	}  // rgb format
	else if (bpp == 3) {
		if (surf->format->Rmask == 255) {
			format = GL_RGB8;
		} else {
			format = GL_BGR;
		}
	} else {
		std::string message = "IMG error: File '" + filepath + "' Unkown bpp format = " + std::to_string(bpp) + "!";
		std::cout << message << '\n';
		return;
	}
	FlipVertical();  // flip pixels to match OpenGL system

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, flipped_pixels_);
	Unbind();
}

void TextureManager::Load(const std::string& textureName, const std::string& filepath, GLenum minFilter, GLenum magFilter) {
	textures[textureName] = std::make_shared<Texture>(filepath, minFilter, magFilter);
}

void TextureManager::Load(const std::string& textureName, SDL_Surface* surface, GLenum minFilter, GLenum magFilter) {
	textures[textureName] = std::make_shared<Texture>(surface, minFilter, magFilter);
}

Sptr<Texture> TextureManager::Get(const std::string& textureName) {
	return textures[textureName];
}

bool TextureManager::Contains(const std::string& textureName) {
	return textures.find(textureName) != textures.end();
}

Sptr<Texture> TextureManager::operator[](const std::string& textureName) {
	return Get(textureName);
}

}  // namespace libgl
