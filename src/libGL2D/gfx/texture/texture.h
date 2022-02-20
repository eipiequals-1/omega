#ifndef _LIBGL2D_GFX_TEXTURE_TEXTURE_H_
#define _LIBGL2D_GFX_TEXTURE_TEXTURE_H_

#include <GL/gl.h>
#include <SDL2/SDL_image.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "libGL2D/core/using.h"
#include "libGL2D/gfx/errors.h"

namespace libGL2D {

class Texture {
   public:
	explicit Texture(const std::string& filepath, GLenum minFilter = GL_LINEAR, GLenum magFilter = GL_LINEAR);
	explicit Texture(SDL_Surface* surf, GLenum minFilter = GL_LINEAR, GLenum magFilter = GL_LINEAR);
	~Texture();

	void Bind(uint32_t slot = 0) const;
	void Unbind() const;
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	void SaveToFile(const std::string& filepath);

	void FlipVertical();

   private:
	void Load(bool flipVertical = true, GLenum minFilter = GL_LINEAR, GLenum magFilter = GL_LINEAR);
	GLuint id;
	std::string filepath;

	SDL_Surface* surf;

	GLsizei width, height;
	uint8_t bpp;  // bytes per pixel
};

class TextureManager {
   public:
	void Load(const std::string& textureName, const std::string& filepath, GLenum minFilter = GL_LINEAR, GLenum magFilter = GL_LINEAR);
	void Load(const std::string& textureName, SDL_Surface* surface, GLenum minFilter = GL_LINEAR, GLenum magFilter = GL_LINEAR);

	Sptr<Texture> Get(const std::string& textureName);
	bool Contains(const std::string& textureName);

	Sptr<Texture> operator[](const std::string& textureName);

   private:
	std::unordered_map<std::string, Sptr<Texture>> textures;
};

}  // namespace libGL2D

#endif  // _LIBGL2D_GFX_TEXTURE_TEXTURE_H_