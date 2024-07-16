#ifndef OMEGA_SCENE_TILED_MAPRENDERER_HPP
#define OMEGA_SCENE_TILED_MAPRENDERER_HPP

#include <cstdint>
#include <string>
#include <vector>

#include "omega/gfx/frame_buffer.hpp"
#include "omega/gfx/sprite_batch.hpp"
#include "omega/gfx/texture/texture.hpp"
#include "omega/scene/tiled/map.hpp"
#include "omega/util/util.hpp"

namespace omega::scene::tiled {

/**
 * Renders the tiled map by converting each layer into 1 texture for much faster
 * rendering
 */
class MapRenderer {
  public:
    explicit MapRenderer(Map *map, const std::string &tileset_path);
    virtual void setup(gfx::SpriteBatch &sprite_batch);
    virtual ~MapRenderer();

    /**
     * Renders the tiled map
     * @param batch for rendering
     */
    virtual void render(gfx::SpriteBatch &batch);

  protected:
    Map *map = nullptr;
    std::vector<gfx::FrameBuffer *> layers;
    std::vector<util::sptr<gfx::texture::Texture>> layer_textures;

    std::vector<util::sptr<gfx::texture::Texture>> tileset_textures;
};
} // namespace omega::scene::tiled

#endif // OMEGA_SCENE_TILED_MAPRENDERER_HPP
