#ifndef _TEXTUREPACKER_TEX_H_
#define _TEXTUREPACKER_TEX_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>

namespace packer {

struct Tex {
	Tex(const std::string &input_dir, const std::string &filename) : filepath(filename) {
		surf = IMG_Load((input_dir + filepath).c_str());
		if (surf == nullptr) {
			std::cout << "Unable to load surface \"" << input_dir + filepath << "\" \n";
		}
		x = 0;
		y = 0;
	}
	std::string GetKey() const {
		return filepath.substr(0, filepath.size() - 4);
	}
	uint32_t Area() const {
		return surf->w * surf->h;
	}
	~Tex() {
		if (surf != nullptr) {
			SDL_FreeSurface(surf);
		}
		surf = nullptr;
	}
	SDL_Surface *surf;
	std::string filepath;
	uint32_t x, y;
};

}  // namespace packer

#endif  // _TEXTUREPACKER_TEX_H_