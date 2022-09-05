#ifndef OMEGA_GFX_TEXTURE_TEXTUREATLAS_H
#define OMEGA_GFX_TEXTURE_TEXTUREATLAS_H

#include <GL/gl.h>

#include <string>
#include <unordered_map>

#include "omega/gfx/texture/texture.h"
#include "omega/gfx/texture/texture_region.h"
#include "omega/util/util.h"

namespace omega {

/**
 * Represents every "sub-texture" or TextureRegion of a larger texture
 * for faster rendering both on CPU and GPU side.
 * A TextureAtlas can only be created from a libgl atlas file
 * made with the tools/texture_packer package.
 */
class TextureAtlas {
   public:
	explicit TextureAtlas(const std::string &atlas_file_path, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_NEAREST);
	~TextureAtlas();

	/**
	 * Returns the texture with the given look-up string
	 * @param texture_name name of the texture region as defined by the atlas file
	 * @return shared pointer to the TextureRegion
	 */
	sptr<TextureRegion> Get(const std::string &texture_name);

	/**
	 * @returns the texture that the atlas is a wrapper of
	 */
	sptr<Texture> GetTexture() const { return tex_; };

   private:
	std::unordered_map<std::string, sptr<TextureRegion>> tex_regions_;
	sptr<Texture> tex_;
};
}  // namespace omega

#endif  // OMEGA_GFX_TEXTURE_TEXTUREATLAS_H