#ifndef EDITOR_PANELS_RESOURCEPANEL_H
#define EDITOR_PANELS_RESOURCEPANEL_H

#include "omega/gfx/gfx.h"
#include "omega/gfx/texture/texture.h"
#include "omega/scene/scene.h"
#include "omega/util/util.h"

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