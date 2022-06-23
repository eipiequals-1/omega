#ifndef _LIBGL2D_GFX_TEXTURE_TEXTURE_H_
#define _LIBGL2D_GFX_TEXTURE_TEXTURE_H_

#include <GL/gl.h>
#include <SDL2/SDL_image.h>

#include <cstring>
#include <memory>
#include <string>
#include <unordered_map>

#include "libGL2D/core/using.h"
#include "libGL2D/gfx/errors.h"

namespace libgl {

/**
 * Abstraction of OpenGL texture to be used with a SpriteBatch
 * or a custom renderer.
 */
class Texture {
   public:
	explicit Texture(const std::string& filepath, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_NEAREST);
	Texture(uint32_t width, uint32_t height, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_NEAREST);

	~Texture();

	/**
	 * Binds this texture as the active OpenGL texture to the given slot
	 * @param slot to bind to
	 */
	void Bind(uint32_t slot = 0) const;

	/**
	 * Unbind the texture in OpenGL
	 */
	void Unbind() const;

	uint32_t GetWidth() const { return width_; }
	uint32_t GetHeight() const { return height_; }

	/**
	 * Sets the texture data for RGBA textures using a uint32_t array
	 * @param data with RGBA data
	 */
	void SetData(uint32_t* data) {
		if (pixels_ != nullptr) {
			delete[] pixels_;
			pixels_ = nullptr;
		}
		pixels_ = new uint32_t[width_ * height_];
		std::memcpy(pixels_, data, sizeof(uint32_t) * width_ * height_);
		glBindTexture(GL_TEXTURE_2D, id_);  // bind without setting active texture
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width_, height_, GL_RGBA, GL_UNSIGNED_BYTE, data);
		Unbind();
	}
	const uint32_t* GetPixels() const {
		return pixels_;
	}

	/**
	 * Static factory method that creates a dynamically allocated texture from an SDL_Surface which is not destroyed
	 * @param surf pointer to SDL_Surface
	 * @param min_filter type of filter for minimizing the texture
	 * @param max_filter type of filter for maximizing the texture
	 * @return a new Texture
	 */
	static Texture* FromSurface(SDL_Surface* surf, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_NEAREST) {
		Texture* tex = new Texture(surf->w, surf->h, min_filter, mag_filter);
		tex->SetData((uint32_t*)surf->pixels);
		return tex;
	}

   private:
	/**
	 * Creates the texture and sets the min, mag, and wrap filters
	 */
	void Load();

	GLuint id_;
	GLenum min_filter_, mag_filter_;
	uint32_t* pixels_;  // store the pixels in OpenGL coords
	uint32_t width_, height_;
};

/**
 * Generic TextureManager for cheaper and faster look-ups using an unordered map
 * Best Key for fastest lookup is an int or enum
 */
template <typename K>
class TextureManager {
   public:
	/**
	 * Loads the texture at the given filepath and adds it to the map
	 * @param id key for look-up
	 * @param filepath relative or absolute path
	 * @param min_filter type of filter for minimizing the texture
	 * @param max_filter type of filter for maximizing the texture
	 */
	void Load(const K& id, const std::string& filepath, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_NEAREST) {
		if (!Contains(id)) {
			textures_[id] = std::make_shared<Texture>(filepath, min_filter, mag_filter);
		}
	}

	/**
	 * Loads the texture at the given filepath and adds it to the map
	 * @param id key for look-up
	 * @param surface relative or absolute path
	 * @param min_filter type of filter for minimizing the texture
	 * @param max_filter type of filter for maximizing the texture
	 */
	void Load(const K& id, SDL_Surface* surface, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_NEAREST) {
		if (!Contains(id)) {
			textures_[id] = Sptr<Texture>(Texture::FromSurface(surface, min_filter, mag_filter));
		}
	}

	/**
	 * Returns a libgl::Sptr to the texture based off of the given id
	 * IMPORTANT: if the id is invalid, this case is not handled
	 * @param id look-up id
	 * @return the texture
	 */
	Sptr<Texture> Get(const K& id) {
		return textures_[id];
	}

	/**
	 * Returns if there is already a texture at the given id
	 * @param id the id of the texture
	 * @return if there is already a texture
	 */
	bool Contains(const K& id) {
		return textures_.find(id) != textures_.end();
	}

	/**
	 * Another easy look-up method
	 * Same as Sptr<Texture> Get(const K& id);
	 */
	Sptr<Texture> operator[](const K& id) {
		return Get(id);
	}

   private:
	std::unordered_map<K, Sptr<Texture>> textures_;
};

}  // namespace libgl

#endif  // _LIBGL2D_GFX_TEXTURE_TEXTURE_H_