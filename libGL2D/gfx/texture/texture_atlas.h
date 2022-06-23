#ifndef _LIBGL2D_GFX_TEXTURE_TEXTUREATLAS_H_
#define _LIBGL2D_GFX_TEXTURE_TEXTUREATLAS_H_

#include <GL/gl.h>

#include <string>
#include <unordered_map>

#include "libGL2D/core/using.h"
#include "libGL2D/gfx/texture/texture.h"
#include "libGL2D/gfx/texture/texture_region.h"

namespace libgl {

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
	Sptr<TextureRegion> Get(const std::string &texture_name);

	/**
	 * @returns the texture that the atlas is a wrapper of
	 */
	Sptr<Texture> GetTexture() const { return tex_; };

   private:
	std::unordered_map<std::string, Sptr<TextureRegion>> tex_regions_;
	Sptr<Texture> tex_;
};
}  // namespace libgl

#endif  // _LIBGL2D_GFX_TEXTURE_TEXTUREATLAS_H_