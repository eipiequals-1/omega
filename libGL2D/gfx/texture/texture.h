#ifndef _LIBGL2D_GFX_TEXTURE_TEXTURE_H_
#define _LIBGL2D_GFX_TEXTURE_TEXTURE_H_

#include <GL/gl.h>
#include <SDL2/SDL_image.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "libGL2D/core/using.h"
#include "libGL2D/gfx/errors.h"

namespace libgl {

class Texture {
   public:
	explicit Texture(const std::string& filepath, GLenum minFilter = GL_NEAREST, GLenum magFilter = GL_NEAREST);
	explicit Texture(SDL_Surface* surf, GLenum minFilter = GL_NEAREST, GLenum magFilter = GL_NEAREST);
	explicit Texture(uint32_t* pixels, uint32_t width, uint32_t height, GLenum minFilter = GL_NEAREST, GLenum magFilter = GL_NEAREST);
	~Texture();

	void Bind(uint32_t slot = 0) const;
	void Unbind() const;
	int get_width() const { return width; }
	int get_height() const { return height; }
	void SaveToFile(const std::string& filepath);

	void FlipVertical();
	uint32_t* get_sdl_pixels() const {
		return (uint32_t*)surf->pixels;
	}
	uint32_t* get_opengl_pixels() const {
		return flipped_pixels_;
	}

   private:
	void Load(GLenum minFilter = GL_NEAREST, GLenum magFilter = GL_NEAREST);
	GLuint id;
	std::string filepath;

	SDL_Surface* surf;
	uint32_t* flipped_pixels_;  // store the pixels in OpenGL coords

	GLsizei width, height;
	uint8_t bpp;  // bytes per pixel
};

template <typename K>
class TextureManager {
   public:
	void Load(const K& id, const std::string& filepath, GLenum minFilter = GL_NEAREST, GLenum magFilter = GL_NEAREST) {
		textures_[id] = std::make_shared<Texture>(filepath, minFilter, magFilter);
	}
	void Load(const K& id, SDL_Surface* surface, GLenum minFilter = GL_NEAREST, GLenum magFilter = GL_NEAREST) {
		textures_[id] = std::make_shared<Texture>(surface, minFilter, magFilter);
	}

	Sptr<Texture> Get(const K& id) {
		return textures_[id];
	}

	bool Contains(const K& id) {
		return textures_.find(id) != textures_.end();
	}

	Sptr<Texture> operator[](const K& id) {
		return Get(id);
	}

   private:
	std::unordered_map<K, Sptr<Texture>> textures_;
};

}  // namespace libgl

#endif  // _LIBGL2D_GFX_TEXTURE_TEXTURE_H_