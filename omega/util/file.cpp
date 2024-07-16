#include "file.hpp"

#include <filesystem>

namespace omega::util::file {

std::string get_path(const std::string &file) {
    // PROJ
    //   SRC
    //   RES
    //   LIB
    //     OMEGA
    //       OMEGA
    //       RES
    std::filesystem::path cwd = std::filesystem::current_path();

    if (cwd.string().ends_with("")) {}

    return cwd.string();
}

} // namespace omega::util::file
