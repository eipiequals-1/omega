#include "texture.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace omega::gfx::texture {

Texture::Texture(u32 width, u32 height,
                 TextureParam min_filter, TextureParam mag_filter) :
id(0), width(width), height(height) {

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    // if rendered smaller, use giver filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (i32) min_filter);
    // if rendered larger, use given filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (i32) mag_filter);
    // continue closest color to edge
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    load(nullptr);
    unbind();
}

Texture::Texture(u32 id, u32 width, u32 height) :
id(id), width(width), height(height) {
}


Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::bind(u32 slot) const {
    glActiveTexture(GL_TEXTURE0 + slot); // which slot the next texture will use
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::load(u32 *pixels) {
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    unbind();
}

util::uptr<u32[]> Texture::get_pixels() {
    auto pixels = std::make_unique<u32[]>(width * height);

    glBindTexture(GL_TEXTURE_2D, id);
#ifdef EMSCRIPTEN
    omega::util::err("Functionality not available for GLES2!");
#else
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.get());
#endif
    glBindTexture(GL_TEXTURE_2D, 0);
    return pixels;
}

} // namespace omega::gfx::texture
