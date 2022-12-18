#include "texture.h"

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace omega::gfx::texture {

Texture::Texture(u32 width, u32 height, GLenum min_filter, GLenum mag_filter) : id(0), width(width), height(height) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);   // if rendered smaller, use giver filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);   // if rendered larger, use given filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // continue closest color to edge
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    load(nullptr);
    unbind();
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::bind(GLuint slot) const {
    glActiveTexture(GL_TEXTURE0 + slot); // which slot the next texture will use
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::load(u32 *pixels) {
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    unbind();
}

uptr<u32[]> Texture::get_pixels() {
    auto pixels = std::make_unique<u32[]>(width * height);

    glBindTexture(GL_TEXTURE_2D, id);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.get());
    glBindTexture(GL_TEXTURE_2D, 0);
    return pixels;
}

} // namespace omega::gfx::texture
