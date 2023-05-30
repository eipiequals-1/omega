#include <dirent.h>
#include <string.h>

#include <iostream>
#include <vector>

#include "packer.hpp"

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

int main() {
	std::string input_dir_name;
	std::string output_dir_name;
	std::string pack_name;
	Prompt("Where are the textures located? (absolute path)  ", input_dir_name);
	Prompt("Where should the textures be outputted? (absolute path)  ", output_dir_name);
	Prompt("What should your atlas be called?  ", pack_name);

	std::vector<std::string> png_files;  // names of all pngs

	// open file
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
		return 1;
	}
	// pack the textures
	packer::Pack(input_dir_name, output_dir_name, pack_name, png_files);
	// give final messages
	std::cout << "Success!\n\n";
	std::cout << "Saved to " << output_dir_name << pack_name << ".atlas\n";
	std::cout << "Remember to open the texture atlas in GIMP to be able to use it properly\n";

	return 0;
}
