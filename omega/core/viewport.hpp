#ifndef OMEGA_CORE_VIEWPORT_HPP
#define OMEGA_CORE_VIEWPORT_HPP

#include "omega/gfx/gl.hpp"

#include "omega/util/math.hpp"
#include "omega/util/types.hpp"

namespace omega::core {

/**
 * Specify the type of Viewport
 */
enum class ViewportType {
    fit,     // keep aspect ratio to take up max space on the screen
    stretch, // world is scaled to take up the full screen
};

/**
 * Abstraction and management of glViewport handling resizing in different 
 * ViewportType configurations
 */
class Viewport {
  public:
    /**
     * Constructs a glViewport from the given params
     * @param viewport_type
     * @param initial_width
     * @param initial_height
     */
    Viewport(
        ViewportType viewport_type,
        u32 initial_width,
        u32 initial_height);
    ~Viewport() = default;

    /**
     * Performs glViewport to maintain the ViewportType using the new width and
     * height
     * @param new_width
     * @param new_height
     * @return the glViewport params
     */
    glm::rect<u32> on_resize(u32 new_width, u32 new_height);
    /**
     * @return the viewport width
     */
    u32 get_width() const { return current_width; }
    /**
     * @return the viewport height
     */
    u32 get_height() const { return current_height; }

  private:
    ViewportType viewport_type = ViewportType::stretch;
    // initial settings (for aspect ratio)
    u32 initial_width;
    u32 initial_height;
    // current settings
    u32 current_width;
    u32 current_height;
};

} // namespace omega::core

#endif // OMEGA_CORE_VIEWPORT_HPP
