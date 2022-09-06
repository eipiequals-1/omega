#include "map_renderer.h"

namespace omega::map {

MapRenderer::MapRenderer(Map *map, const std::string &tileset_path) : map(map) {
    std::string path;
    tex_manager = create_uptr<TextureManager<u32>>();
    for (size_t i = 0; i < map->tilesetCollection.size(); ++i) {
        const auto &tileset = map->tilesetCollection[i];
        path = tileset.image.source;
        tex_manager->load(i, tileset_path + "/" + path, GL_NEAREST, GL_NEAREST);
    }
    // create new texture per layer
    for (const auto &layer : map->layerCollection) {
        if (layer.visible) {
            load_layer(layer);
        }
    }
}

MapRenderer::~MapRenderer() {
}

void MapRenderer::load_layer(const Layer &layer) {
    u32 tile_width = map->tileWidth;
    u32 tile_height = map->tileHeight;
    u32 layer_width_pix = tile_width * layer.width;
    u32 layer_height_pix = tile_height * layer.height;
    // use u32 for each pixel
    // 1 byte / color component
    u32 num_pixels = layer_width_pix * layer_height_pix; // allocate area of all pixels
    std::vector<u32> pixels;
    pixels.resize(num_pixels);
    // for every tile copy the respective tile section to the pixel buffer
    for (size_t tile_idx = 0; tile_idx < layer.tiles.size(); ++tile_idx) {
        const Tile &tile = layer.tiles[tile_idx];
        // find location of first pixel of tile
        u32 row, col, start_x, start_y;
        col = tile_idx % layer.width; // col in tile units
        row = tile_idx / layer.width; // row in tile units
        start_x = col * tile_width;   // x offset in pixels
        start_y = row * tile_height;  // y offset in pixels
        // get pointer to first pixel of tile
        u32 *pix = &pixels[start_y * layer_width_pix + start_x];
        set_tile_pixels(pix, tile, layer_width_pix, layer_height_pix);
    }
    layer_texture.push_back(Texture::create_empty(layer_width_pix, layer_height_pix, GL_NEAREST, GL_NEAREST));
    (layer_texture.end() - 1)->get()->set_data(pixels.data());
}

void MapRenderer::render(SpriteBatch &batch) {
    for (const auto &layer : layer_texture) {
        batch.render_texture(layer.get(), 0.0f, 0.0f);
    }
}

} // namespace omega::map
