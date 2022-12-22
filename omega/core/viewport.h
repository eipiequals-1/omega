#ifndef OMEGA_CORE_VIEWPORT_H
#define OMEGA_CORE_VIEWPORT_H

#include <GL/gl.h>

#include "omega/util/util.h"

namespace omega::core {

enum class ViewportType {
    fit,     // keep aspect ratio to take up max space on the screen
    stretch, // world is scaled to take up the full screen
};

class Viewport {
  public:
    Viewport(ViewportType viewport_type, uint32_t initial_width, uint32_t initial_height);
    virtual ~Viewport();

    virtual glm::rect<uint32_t> on_resize(uint32_t new_width, uint32_t new_height);
    uint32_t get_width() const { return current_width; }
    uint32_t get_height() const { return current_height; }

  private:
    ViewportType viewport_type;
    uint32_t initial_width;
    uint32_t initial_height;
    uint32_t current_width;
    uint32_t current_height;
};

} // namespace omega::core

#endif // OMEGA_CORE_VIEWPORT_H