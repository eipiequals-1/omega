#include "mask.hpp"

namespace omega::util {

Mask::Mask(u32* data, u32 width, u32 height, i32 alpha_threshold) {
    this->width = width;
    this->height = height;

    mask_data = new u32[width * height];

    for (u32 y = 0; y < height; ++y) {
        for (u32 x = 0; x < width; ++x) {
            u8* pixel = (u8 *) &data[y * width + x];
            u8 a = pixel[3];

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

uptr<Mask> Mask::from_texture(gfx::texture::Texture *texture, i32 alpha_threshold) {
    u32* pixels = texture->get_pixels().get();
    return create_uptr<Mask>(pixels, texture->get_width(),
                             texture->get_height(), alpha_threshold);
}

bool Mask::collide_with(const glm::rectf &rect, const glm::vec2 &mask_pos) {
    // iterate through all pixels that intersect the rectangle
    u32 start_x = 0, start_y = 0, end_x = 0, end_y = 0;
    start_x = glm::max(rect.x, mask_pos.x);
    end_x = glm::min(rect.x + rect.w, mask_pos.x + width);
    start_y = glm::max(rect.y, mask_pos.y);
    end_y = glm::min(rect.y + rect.h, mask_pos.y + height);

    for (u32 y = start_y; y <= end_y; ++y) {
        for (u32 x = start_x; x <= end_x; ++x) {
            // if the pixel is not empty, return true
            i32 local_mask_x = x - mask_pos.x;
            i32 local_mask_y = y - mask_pos.y;

            if (mask_data[local_mask_y * width + local_mask_x] != 0) {
                return true;
            }
        }
    }
    return false;
}


bool Mask::collide_with(const Mask& other, const glm::vec2 &other_pos,
                        const glm::vec2 &mask_pos) {
     // iterate through all pixels that intersect the rectangle
    u32 start_x = 0, start_y = 0, end_x = 0, end_y = 0;
    start_x = glm::max(other_pos.x, mask_pos.x);
    end_x = glm::min(other_pos.x + other.width, mask_pos.x + width);
    start_y = glm::max(other_pos.y, mask_pos.y);
    end_y = glm::min(other_pos.y + other.height, mask_pos.y + height);

    for (u32 y = start_y; y <= end_y; ++y) {
        for (u32 x = start_x; x <= end_x; ++x) {
            // if the both pixels are not empty, return true
            i32 local_mask_x = x - mask_pos.x;
            i32 local_mask_y = y - mask_pos.y;

            i32 local_other_x = x - other_pos.x;
            i32 local_other_y = y - other_pos.y;

            if (mask_data[local_mask_y * width + local_mask_x] != 0 &&
                other.mask_data[local_other_y * width + local_other_x] != 0) {
                return true;
            }
        }
    }
    return false;
   
}

} // namespace omega::util
