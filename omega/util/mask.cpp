#include "mask.hpp"

namespace omega::util {

Mask::Mask(uint32_t* data, uint32_t width, uint32_t height, int alpha_threshold) {
    this->width = width;
    this->height = height;

    mask_data = new uint32_t[width * height];

    for (uint32_t y = 0; y < height; ++y) {
        for (uint32_t x = 0; x < width; ++x) {
            uint8_t* pixel = (uint8_t *) &data[y * width + x];
            uint8_t a = pixel[3];

            if (a > alpha_threshold) {
                mask_data[y * width + x] = 0xffffffff;
            } else {
                mask_data[y * width + x] = 0x00000000;
            }
        }
    }
}

Mask::~Mask() {
    delete[] mask_data;
    mask_data = nullptr;
}

uptr<Mask> from_texture(gfx::texture::Texture *texture, int alpha_threshold) {
    uint32_t* pixels = texture->get_pixels().get();
    return create_uptr<Mask>(pixels, texture->get_width(),
                             texture->get_height(), alpha_threshold);
}

bool Mask::collide_with(const glm::rectf &rect, const glm::vec2 &mask_pos) {
    // iterate through all pixels that intersect the rectangle
    uint32_t start_x = 0, start_y = 0, end_x = 0, end_y = 0;
    start_x = glm::max(rect.x, mask_pos.x);
    end_x = glm::min(rect.x + rect.w, mask_pos.x + width);
    start_y = glm::max(rect.y, mask_pos.y);
    end_y = glm::min(rect.y + rect.h, mask_pos.y + height);

    for (uint32_t y = start_y; y <= end_y; ++y) {
        for (uint32_t x = start_x; x <= end_x; ++x) {
            // if the pixel is not empty, return true
            if (mask_data[y * width + x] != 0) {
                return true;
            }
        }
    }
    return false;
}


bool Mask::collide_with(const Mask& other, const glm::vec2 &other_pos,
                        const glm::vec2 &mask_pos) {
     // iterate through all pixels that intersect the rectangle
    uint32_t start_x = 0, start_y = 0, end_x = 0, end_y = 0;
    start_x = glm::max(other_pos.x, mask_pos.x);
    end_x = glm::min(other_pos.x + other.width, mask_pos.x + width);
    start_y = glm::max(other_pos.y, mask_pos.y);
    end_y = glm::min(other_pos.y + other.height, mask_pos.y + height);

    for (uint32_t y = start_y; y <= end_y; ++y) {
        for (uint32_t x = start_x; x <= end_x; ++x) {
            // if the both pixels are not empty, return true
            if (mask_data[y * width + x] != 0 &&
                other.mask_data[y * width + x] != 0) {
                return true;
            }
        }
    }
    return false;
   
}

} // namespace omega::util
