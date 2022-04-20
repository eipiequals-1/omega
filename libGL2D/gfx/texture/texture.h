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

class TextureManager {
   public:
	using TextureID = uint32_t;
	void Load(TextureID id, const std::string& filepath, GLenum minFilter = GL_NEAREST, GLenum magFilter = GL_NEAREST);
	void Load(TextureID id, SDL_Surface* surface, GLenum minFilter = GL_NEAREST, GLenum magFilter = GL_NEAREST);

	Sptr<Texture> Get(TextureID id);
	bool Contains(TextureID id);

	Sptr<Texture> operator[](TextureID id);

   private:
	std::unordered_map<TextureID, Sptr<Texture>> textures_;
};

}  // namespace libgl

#endif  // _LIBGL2D_GFX_TEXTURE_TEXTURE_H_