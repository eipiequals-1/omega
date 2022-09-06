#ifndef OMEGA_CORE_VIEWPORT_H
#define OMEGA_CORE_VIEWPORT_H

#include <GL/gl.h>

#include "omega/util/util.h"

namespace omega::core {

enum class ViewportType {
    k_fit,     // keep aspect ratio to take up max space on the screen
    k_stretch, // world is scaled to take up the full screen
};

class Viewport {
  public:
    Viewport(ViewportType viewport_type, u32 initial_width, u32 initial_height);
    virtual ~Viewport();

    virtual void on_resize(u32 new_width, u32 new_height);
    u32 get_viewport_width() const { return current_width; }
    u32 get_viewport_height() const { return current_height; }

  private:
    ViewportType viewport_type;
    u32 initial_width;
    u32 initial_height;
    u32 current_width;
    u32 current_height;
};

} // namespace omega::core

#endif // OMEGA_CORE_VIEWPORT_H