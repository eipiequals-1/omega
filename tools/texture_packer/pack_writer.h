
#ifndef _TEXTUREPACKER_PACKWRITER_H_
#define _TEXTUREPACKER_PACKWRITER_H_

#include <string>
#include <vector>

#include "texture_packer/tex.h"

namespace packer {
void WriteFile(const std::vector<Tex *> &textures, const std::string &output_dir, const std::string &atlas_name, uint32_t width, u_int32_t height);

void CopyTextureTo(Tex *tex, uint32_t *atlas_pixels, uint32_t atlas_width, uint32_t atlas_height);
}  // namespace packer

#endif  // _TEXTUREPACKER_PACKWRITER_H_