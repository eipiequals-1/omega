#ifndef _TEXTUREPACKER_PACKER_H_
#define _TEXTUREPACKER_PACKER_H_

#include <cmath>
#include <memory>
#include <string>
#include <vector>

#include "texture_packer/pack_writer.h"
#include "texture_packer/tex.h"

namespace packer {

struct Size {
	uint32_t width;
	uint32_t height;
};

void Pack(const std::string &input_dir, const std::string &output_dir, const std::string &atlas_name, const std::vector<std::string> &files);

void LoadTextures(std::vector<Tex *> &textures, const std::string &input_dir, const std::vector<std::string> &files);

void FreeTextures(std::vector<Tex *> &textures);

Size Algo(std::vector<Tex *> &textures);

inline unsigned int NextPowerOfTwo(unsigned int x) {
	if (x <= 1) return 1;
	int power = 2;
	x--;
	while (x >>= 1) power <<= 1;
	return power;
}

inline void SortByWidth(std::vector<Tex *> &sorted) {
	// quick insertion sort
	for (size_t i = 1; i < sorted.size(); i++) {
		Tex *el = sorted[i];
		int new_idx = i - 1;
		while (new_idx >= 0 && sorted[new_idx]->surf->w > el->surf->w) {
			// shift current element to lower index
			sorted[new_idx + 1] = sorted[new_idx];
			new_idx--;
		}
		// now element is in currect spot so set it
		sorted[new_idx + 1] = el;
	}
}

inline void SortByHeight(std::vector<Tex *> &sorted) {
	// quick insertion sort
	for (size_t i = 1; i < sorted.size(); i++) {
		Tex *el = sorted[i];
		int new_idx = i - 1;
		while (new_idx >= 0 && sorted[new_idx]->surf->h > el->surf->h) {
			// shift current element to lower index
			sorted[new_idx + 1] = sorted[new_idx];
			new_idx--;
		}
		// now element is in currect spot so set it
		sorted[new_idx + 1] = el;
	}
}

inline void SortBySurfaceArea(std::vector<Tex *> &sorted) {
	// quick insertion sort
	for (size_t i = 1; i < sorted.size(); i++) {
		Tex *el = sorted[i];
		int new_idx = i - 1;
		while (new_idx >= 0 && sorted[new_idx]->Area() > el->Area()) {
			// shift current element to lower index
			sorted[new_idx + 1] = sorted[new_idx];
			new_idx--;
		}
		// now element is in currect spot so set it
		sorted[new_idx + 1] = el;
	}
}
}  // namespace packer

#endif  // _TEXTUREPACKER_PACKER_H_