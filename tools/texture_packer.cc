#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <dirent.h>
#include <string.h>

#include <array>
#include <iostream>
#include <string>
#include <vector>

using byte = unsigned char;

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

static void Prompt(const std::string &p, std::string &s) {
	std::cout << p;
	std::cin >> s;
}

static bool EndsWith(const std::string &s, const std::string &sub) {
	auto iter = s.rbegin();
	auto iter_sub = sub.rbegin();
	while (iter != s.rend() && iter_sub != sub.rend() && *iter == *iter_sub) {
		++iter;
		++iter_sub;
	}
	return iter_sub == sub.rend();
}

static std::vector<Tex *> LoadTextures(const std::string &input_dir_name, const std::vector<std::string> &files) {
	std::vector<Tex *> textures;
	textures.reserve(files.size());
	for (auto &file : files) {
		Tex *tex = new Tex(input_dir_name, file);
		textures.push_back(tex);
	}
	return textures;
}

static void FreeTextures(std::vector<Tex *> &textures) {
	for (auto tex : textures) {
		delete tex;
		tex = nullptr;
	}
}

static void CopyTextureTo(Tex *tex, uint32_t *pixels, uint32_t width) {
	uint32_t *tex_pixels = (uint32_t *)tex->surf->pixels;
	for (int y = 0; y < tex->surf->h; ++y) {
		size_t bytes = sizeof(uint32_t) * tex->surf->w;
		uint32_t output_x, output_y;
		output_x = tex->x + 0;
		output_y = tex->y + y;
		memcpy(&pixels[output_y * width + output_x], &tex_pixels[y * tex->surf->w], bytes);
	}
}

static void WriteFile(const std::vector<Tex *> &textures, const std::string &output_dir, const std::string &atlas_name) {
	uint32_t total_width = 0;
	uint32_t max_height = 0;
	for (auto tex : textures) {
		tex->x = total_width;
		tex->y = 0;
		total_width += tex->surf->w;
		if (tex->surf->h > (int)max_height) {
			max_height = tex->surf->h;
		}
	}
	std::vector<uint32_t> pixels;
	pixels.resize(total_width * max_height);
	for (auto tex : textures) {
		CopyTextureTo(tex, pixels.data(), total_width);
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
	SDL_Surface *tex = SDL_CreateRGBSurfaceFrom(pixels.data(), total_width, max_height, 32, 4 * total_width, rmask, gmask, bmask, amask);
	// save in current working directory
	std::string img = atlas_name + std::string(".png");
	const char *img_file = img.c_str();
	SDL_SaveBMP_RW(tex, SDL_RWFromFile(img_file, "wb"), 1);
	// move to location
	std::string cmd = "mv " + atlas_name + ".png " + (output_dir + img_file);
	system(cmd.c_str());

	SDL_FreeSurface(tex);
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

int main() {
	std::string input_dir_name;
	std::string output_dir_name;
	std::string pack_name;
	Prompt("Where are the textures located?  ", input_dir_name);
	Prompt("Where should the textures be outputted?  ", output_dir_name);
	Prompt("What should your texture be called?  ", pack_name);

	std::vector<std::string> png_files;  // names of all pngs

	DIR *input_dir;
	dirent *dir;
	input_dir = opendir(input_dir_name.c_str());
	if (input_dir != nullptr) {
		// read directory
		while ((dir = readdir(input_dir)) != nullptr) {
			std::string name(dir->d_name);
			// check if png file or link
			if ((dir->d_type == DT_LNK || dir->d_type == DT_REG) && EndsWith(name, ".png")) {
				std::cout << "Processing " << name << std::endl;
				png_files.push_back(name);  // add to files to load
			} else {
				std::cout << "Skipping " << name << std::endl;
			}
		}
		closedir(input_dir);  // cleanup
	} else {
		std::cout << "unable to open directory: \"" << input_dir_name << "\": " << strerror(errno) << std::endl;
	}

	std::cout << "Saving files to \"" << input_dir_name << "\"\n";
	std::vector<Tex *> textures = LoadTextures(input_dir_name, png_files);
	WriteFile(textures, output_dir_name, pack_name);
	std::cout << "Remember to save the open and export file with Gimp to get correct format\n";
	FreeTextures(textures);
	return 0;
}