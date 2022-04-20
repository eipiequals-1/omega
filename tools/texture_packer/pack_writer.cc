#include "texture_packer/pack_writer.h"

namespace packer {

void WriteFile(const std::vector<Tex *> &textures, const std::string &output_dir, const std::string &atlas_name, uint32_t width, u_int32_t height) {
	uint32_t *pixels = new uint32_t[width * height];
	for (uint32_t i = 0; i < width * height; i++) {
		pixels[i] = 0;
	}
	for (auto tex : textures) {
		CopyTextureTo(tex, pixels, width, height);
	}

	uint32_t rmask, gmask, bmask, amask;
	if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	} else {
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	}
	SDL_Surface *tex = SDL_CreateRGBSurfaceFrom(pixels, width, height, 32, 4 * width, rmask, gmask, bmask, amask);
	// save in current working directory
	std::string img = atlas_name + std::string(".png");
	const char *img_file = img.c_str();
	SDL_SaveBMP_RW(tex, SDL_RWFromFile(img_file, "wb"), 1);
	// move to location
	std::string cmd = "mv " + atlas_name + ".png " + (output_dir + img_file);
	system(cmd.c_str());

	SDL_FreeSurface(tex);
	delete[] pixels;
	tex = nullptr;

	// save to atlas
	std::string atlas_path = output_dir + atlas_name + ".atlas";
	FILE *atlas = fopen(atlas_path.c_str(), "w");
	auto write_ln = [&atlas](const std::string &ln) { fputs((ln + "\n").c_str(), atlas); };

	write_ln("src: " + std::string(img_file));

	for (auto tex : textures) {
		write_ln(tex->GetKey());  // write tex name
		write_ln("rect: " + std::to_string(tex->x) + " " + std::to_string(tex->y) + " " + std::to_string(tex->surf->w) + " " + std::to_string(tex->surf->h));
	}
	fclose(atlas);
}

void CopyTextureTo(Tex *tex, uint32_t *atlas_pixels, uint32_t atlas_width, uint32_t atlas_height) {
	(void)atlas_height;
	uint32_t *tex_pixels = (uint32_t *)tex->surf->pixels;
	for (int y = 0; y < tex->surf->h; y++) {
		for (int x = 0; x < tex->surf->w; x++) {
			uint32_t *rgba_data = &tex_pixels[y * tex->surf->w + x];
			atlas_pixels[(tex->y + y) * atlas_width + (tex->x + x)] = *rgba_data;
		}
	}
}
}  // namespace packer