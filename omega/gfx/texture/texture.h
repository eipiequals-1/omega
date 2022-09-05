#ifndef OMEGA_GFX_TEXTURE_TEXTURE_H
#define OMEGA_GFX_TEXTURE_TEXTURE_H

#include <GL/gl.h>
#include <SDL2/SDL_image.h>

#include <cstring>
#include <memory>
#include <string>
#include <unordered_map>

#include "omega/gfx/errors.h"
#include "omega/util/util.h"

namespace omega {

/**
 * Abstraction of OpenGL texture to be used with a SpriteBatch
 * or a custom renderer.
 */
class Texture {
   private:
	Texture(uint32_t width, uint32_t height, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_NEAREST);

   public:
	/**
	 * Static factory method that creates a texture from an SDL_Surface which is not destroyed
	 * @param surf pointer to SDL_Surface
	 * @param min_filter type of filter for minimizing the texture
	 * @param max_filter type of filter for maximizing the texture
	 * @return a new Texture
	 */
	static sptr<Texture> CreateFromSurface(SDL_Surface* surf, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_NEAREST) {
		Texture* tex = new Texture(surf->w, surf->h, min_filter, mag_filter);
		tex->Load((uint32_t*)surf->pixels);
		return sptr<Texture>(tex);
	}

	static sptr<Texture> CreateFromFile(const std::string& filepath, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_NEAREST) {
		SDL_Surface* surf = IMG_Load(filepath.c_str());
		if (surf == nullptr) {
			log("IMG error: Error loading '", filepath, "': ", IMG_GetError());
			return nullptr;
		}
		sptr<Texture> texture = Texture::CreateFromSurface(surf, min_filter, mag_filter);
		SDL_FreeSurface(surf);
		surf = nullptr;
		return texture;
	}

	static sptr<Texture> CreateEmpty(uint32_t width, uint32_t height, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_NEAREST) {
		// must construct using new because constructor is private and not accessible by sptr
		return sptr<Texture>(new Texture(width, height, min_filter, mag_filter));
	}
	~Texture();

	/**
	 * Bind this texture as the active OpenGL texture to the given slot
	 * @param slot to bind to
	 */
	void Bind(uint32_t slot = 0) const;

	/**
	 * Unbind the texture in OpenGL
	 */
	void Unbind() const;
	uint32_t GetRendererID() const { return id_; }

	uint32_t GetWidth() const { return width_; }
	uint32_t GetHeight() const { return height_; }

	/**
	 * Sets the texture data for RGBA textures using a uint32_t array
	 * @param data with RGBA data
	 */
	void SetData(uint32_t* data) {
		glBindTexture(GL_TEXTURE_2D, id_);  // bind without setting active texture
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width_, height_, GL_RGBA, GL_UNSIGNED_BYTE, data);
		Unbind();
	}

	sptr<uint32_t[]> GetPixels();

	static void SaveToFile(const std::string& file_name, uint32_t* pixels, uint32_t width, uint32_t height) {
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
		SDL_Surface* surf = SDL_CreateRGBSurfaceFrom(pixels, width, height, 32, 4 * width, rmask, gmask, bmask, amask);
		// save in current working directory
		SDL_SaveBMP(surf, file_name.c_str());
		SDL_FreeSurface(surf);
	}

   private:
	/**
	 * Creates the texture and sets the min, mag, and wrap filters
	 */
	void Load(uint32_t* pixels);

	GLuint id_;
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
			textures_[id] = Texture::CreateFromFile(filepath, min_filter, mag_filter);
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
			textures_[id] = Texture::CreateFromSurface(surface, min_filter, mag_filter);
		}
	}

	/**
	 * Returns a sptr to the texture based off of the given id
	 * IMPORTANT: if the id is invalid, this case is not handled
	 * @param id look-up id
	 * @return the texture
	 */
	sptr<Texture> Get(const K& id) {
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
	 * Same as sptr<Texture> Get(const K& id);
	 */
	sptr<Texture> operator[](const K& id) {
		return Get(id);
	}

   private:
	std::unordered_map<K, sptr<Texture>> textures_;
};

}  // namespace omega

#endif  // OMEGA_GFX_TEXTURE_TEXTURE_H