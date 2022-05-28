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
	explicit Texture(const std::string& filepath, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_NEAREST);
	Texture(uint32_t width, uint32_t height, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_NEAREST);

	~Texture();

	void Bind(uint32_t slot = 0) const;
	void Unbind() const;
	// void SaveToFile(const std::string& filepath);

	uint32_t get_width() const { return width_; }
	uint32_t get_height() const { return height_; }
	void set_data(const uint32_t* const data) {
		glBindTexture(GL_TEXTURE_2D, id_);  // bind without setting active texture
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width_, height_, GL_RGBA, GL_UNSIGNED_BYTE, data);
		Unbind();
	}
	const uint32_t* get_pixels() const {
		return pixels_;
	}

	/**
	 * Static factory method that creates a dynamically allocated texture from an SDL_Surface
	 * @param surf pointer to SDL_Surface
	 * @param min_filter type of filter for minimizing the texture
	 * @param max_filter type of filter for maximizing the texture
	 */
	static Texture* FromSurface(SDL_Surface* surf, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_NEAREST) {
		Texture* tex = new Texture(surf->w, surf->h, min_filter, mag_filter);
		uint32_t* pixels = (uint32_t*)surf->pixels;
		tex->set_data(pixels);
		return tex;
	}

   private:
	void Load();

	GLuint id_;
	GLenum min_filter_, mag_filter_;
	uint32_t* pixels_;  // store the pixels in OpenGL coords
	uint32_t width_, height_;
};

template <typename K>
class TextureManager {
   public:
	void Load(const K& id, const std::string& filepath, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_NEAREST) {
		textures_[id] = std::make_shared<Texture>(filepath, min_filter, mag_filter);
	}
	void Load(const K& id, SDL_Surface* surface, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_NEAREST) {
		textures_[id] = std::make_shared<Texture>(surface, min_filter, mag_filter);
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