#include "packer.hpp"

namespace packer {

void Pack(const std::string &input_dir, const std::string &output_dir, const std::string &atlas_name, const std::vector<std::string> &files) {
	std::vector<Tex *> textures;
	LoadTextures(textures, input_dir, files);
	Size atlas_width = Algo(textures);
	WriteFile(textures, output_dir, atlas_name, atlas_width.width, atlas_width.height);
	// delete memory
	FreeTextures(textures);
}

void LoadTextures(std::vector<Tex *> &textures, const std::string &input_dir, const std::vector<std::string> &files) {
	for (auto &file : files) {
		Tex *t = new Tex(input_dir, file);
		textures.push_back(t);
	}
}

void FreeTextures(std::vector<Tex *> &textures) {
	for (Tex *t : textures) {
		delete t;
		t = nullptr;
	}
}

Size Algo(std::vector<Tex *> &textures) {
	std::vector<Tex *> sorted = textures;
	SortByHeight(sorted);
	uint32_t surface_area = 0;
	for (const auto &tex : textures) {
		surface_area += tex->Area();
	}
	std::vector<Tex *> sort_width = textures;
	SortByWidth(sort_width);
	uint32_t width = std::max(sort_width.back()->surf->w, (int)ceil(sqrt(surface_area)));  // estimate width
	uint32_t x = 0;
	uint32_t y = 0;
	uint32_t row_height = 0;
	// pack by height from left to right
	for (int idx = sorted.size() - 1; idx >= 0; idx--) {
		Tex *tex = sorted[idx];
		// check if it goes over width
		if (x + tex->surf->w >= width) {
			x = 0;  // start new row
			y += row_height;
			row_height = 0;
		}
		// these are the coords of the textures
		tex->x = x;
		tex->y = y;

		x += tex->surf->w;
		// update row_height
		row_height = std::max(row_height, (uint32_t)tex->surf->h);
	}
	return {width, y + row_height};
}
}  // namespace packer
