#include "texture.h"

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

namespace libGL2D {

Texture::Texture(const std::string& filepath, GLenum minFilter, GLenum magFilter) : id(0), filepath(filepath), surf(nullptr), width(0), height(0) {
	surf = IMG_Load(filepath.c_str());
	if (surf == nullptr) {
		std::cout << "IMG error: Error loading '" + filepath + "': " + IMG_GetError() << "\n";
		return;
	}
	width = surf->w;
	height = surf->h;
	Load(minFilter, magFilter);
}

Texture::Texture(SDL_Surface* surf, GLenum minFilter, GLenum magFilter) : id(0), surf(surf), width(0), height(0) {
	if (surf == nullptr) {
		std::cout << "SDL_Surface error: Invalid Surface (surf = nullptr)\n";
	}
	width = surf->w;
	height = surf->h;
	std::cout << "width: " << width << ", height: " << height << "\n";
	std::cout << "bpp: " << (int)surf->format->BytesPerPixel << "\n";
	std::cout << ": " << (surf->format->Rmask == 255) << "\n";
	Load(minFilter, magFilter);
}

Texture::~Texture() {
	glDeleteTextures(1, &id);
	if (surf != nullptr) SDL_FreeSurface(surf);
	surf = nullptr;
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
	// std::cout << SDL_SaveBMP_RW(surf, SDL_RWFromFile(filepath.c_str(), "wb"), 1) << std::endl;
}

void Texture::FlipVertical() {
	GLuint* pixels = (GLuint*)surf->pixels;
	for (int row = 0; row < height / 2; row++) {
		for (int col = 0; col < width; col++) {
			int originalPixIdx = row * width + col;
			GLuint* originalPix = &pixels[originalPixIdx];

			int reflectPixIdx = (height - 1 - row) * width + col;
			GLuint* reflectPix = &pixels[reflectPixIdx];
			// swap
			GLuint copyReflect = *reflectPix;  // copy of data
			*reflectPix = *originalPix;
			*originalPix = copyReflect;
			// GLubyte* colors = (GLubyte*)originalPix;
			// printf("%u, %u, %u, %u\n", colors[0], colors[1], colors[2], colors[3]);
		}
	}
}

void Texture::Load(bool flipVertical, GLenum minFilter, GLenum magFilter) {
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
	if (flipVertical) {
		FlipVertical();  // flip pixels to match OpenGL system
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, surf->pixels);
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

}  // namespace libGL2D
