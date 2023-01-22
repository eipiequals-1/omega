#ifndef EDITOR_PANELS_RESOURCEPANEL_H
#define EDITOR_PANELS_RESOURCEPANEL_H

#include "omega/gfx/gfx.hpp"
#include "omega/gfx/texture/texture.hpp"
#include "omega/scene/scene.hpp"
#include "omega/util/std.hpp"

namespace omega {

class ResourcePanel {
  public:
    ResourcePanel();
    ~ResourcePanel();

    void render();

  private:
    util::sptr<gfx::texture::Texture> file_texture;
    util::sptr<gfx::texture::Texture> directory_texture;
};

} // namespace omega

#endif // EDITOR_PANELS_RESOURCEPANEL_H
