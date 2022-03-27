#ifndef _LIBGL2D_GFX_TEXTURE_TEXTUREATLAS_H_
#define _LIBGL2D_GFX_TEXTURE_TEXTUREATLAS_H_

#include <string>
#include <unordered_map>

#include "libGL2D/core/using.h"
#include "libGL2D/gfx/texture/texture.h"
#include "libGL2D/gfx/texture/texture_region.h"

namespace libgl {

class TextureAtlas {
   public:
	explicit TextureAtlas(const std::string &atlas_file_path);
	~TextureAtlas();
	Sptr<TextureRegion> Get(const std::string &texture_name);
	Sptr<Texture> get_texture() const { return tex_; };

   private:
	std::unordered_map<std::string, Sptr<TextureRegion>> tex_regions_;
	Sptr<Texture> tex_;
};
}  // namespace libgl

#endif  // _LIBGL2D_GFX_TEXTURE_TEXTUREATLAS_H_