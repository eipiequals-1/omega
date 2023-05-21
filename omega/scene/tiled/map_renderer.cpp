#include "map_renderer.hpp"

#include "omega/scene/orthographic_camera.hpp"

namespace omega::scene::tiled {

MapRenderer::MapRenderer(Map *map) : map(map) {
    std::string path;

    for (size_t i = 0; i < map->tilesetCollection.size(); ++i) {
        const auto &tileset = map->tilesetCollection[i];
        path = tileset.image.source;
        tileset_textures.push_back(
            gfx::texture::Texture::create_from_file(path));
    }
}

MapRenderer::~MapRenderer() {
}

void MapRenderer::setup(gfx::SpriteBatch &sprite_batch) {
    uint32_t tile_width = map->tileWidth;
    uint32_t tile_height = map->tileHeight;
    uint32_t layer_width_pix = tile_width * map->width;
    uint32_t layer_height_pix = tile_height * map->height;
    OrthographicCamera camera(0.0f, layer_width_pix,
                              0.0f, layer_height_pix);

    camera.recalculate_view_matrix();
    sprite_batch.set_view_projection_matrix(
        camera.get_view_projection_matrix());

    for (Layer &layer : map->layerCollection) {
        for (size_t tile_idx = 0; tile_idx < layer.tiles.size(); ++tile_idx) {
            const Tile &tile = layer.tiles[tile_idx];
            // find location of first pixel of tile
            uint32_t row, col, start_x, start_y;
            col = tile_idx % layer.width; // col in tile units
            row = tile_idx / layer.width; // row in tile units
            start_x = col * tile_width;   // x offset in pixels
            start_y = row * tile_height;  // y offset in pixels
            (void)start_y;
            (void)start_x;
            (void)col;
            (void)row;
            (void)tile;
        }
    }

}

void MapRenderer::render(gfx::SpriteBatch &batch) {
    for (const auto &layer : tileset_textures) {
        batch.render_texture(layer.get(), 0.0f, 0.0f);
    }
}

} // namespace omega::scene::tiled
