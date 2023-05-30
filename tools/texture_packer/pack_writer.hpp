#ifndef PACKWRITER_HPP
#define PACKWRITER_HPP

#include <string>
#include <vector>

#include "tex.hpp"

namespace packer {
void WriteFile(const std::vector<Tex *> &textures, const std::string &output_dir, const std::string &atlas_name, uint32_t width, u_int32_t height);

void CopyTextureTo(Tex *tex, uint32_t *atlas_pixels, uint32_t atlas_width, uint32_t atlas_height);
}  // namespace packer

#endif // PACKWRITER_HPP
