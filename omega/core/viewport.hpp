#ifndef OMEGA_CORE_VIEWPORT_H
#define OMEGA_CORE_VIEWPORT_H

#include <GL/gl.h>

#include "omega/util/math.hpp"

namespace omega::core {

/**
 * Specify the type of Viewport
 */
enum class ViewportType {
    fit,     // keep aspect ratio to take up max space on the screen
    stretch, // world is scaled to take up the full screen
};

/**
 * Abstraction and management of glViewport handling resizing in different ViewportType configurations
 */
class Viewport {
  public:
    /**
     * Constructs a glViewport from the given params
     * @param viewport_type
     * @param initial_width
     * @param initial_height
     */
    Viewport(ViewportType viewport_type, uint32_t initial_width, uint32_t initial_height);
    ~Viewport() = default;

    /**
     * Performs glViewport to maintain the ViewportType using the new width and height
     * @param new_width
     * @param new_height
     * @return the glViewport params
     */
    glm::rect<uint32_t> on_resize(uint32_t new_width, uint32_t new_height);
    /**
     * @return the viewport width
     */
    uint32_t get_width() const { return current_width; }
    /**
     * @return the viewport height
     */
    uint32_t get_height() const { return current_height; }

  private:
    ViewportType viewport_type = ViewportType::stretch;
    // initial settings (for aspect ratio)
    uint32_t initial_width;
    uint32_t initial_height;
    // current settings
    uint32_t current_width;
    uint32_t current_height;
};

} // namespace omega::core

#endif // OMEGA_CORE_VIEWPORT_H
