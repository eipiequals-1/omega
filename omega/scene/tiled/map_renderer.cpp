#include "map_renderer.hpp"

namespace omega::scene::tiled {

MapRenderer::MapRenderer(Map *map, const std::string &tileset_path) : map(map) {
    std::string path;
    tex_manager = create_uptr<TextureManager<uint32_t>>();
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
    uint32_t tile_width = map->tileWidth;
    uint32_t tile_height = map->tileHeight;
    uint32_t layer_width_pix = tile_width * layer.width;
    uint32_t layer_height_pix = tile_height * layer.height;
    // use uint32_t for each pixel
    // 1 byte / color component
    uint32_t num_pixels = layer_width_pix * layer_height_pix; // allocate area of all pixels
    std::vector<uint32_t> pixels;
    pixels.resize(num_pixels);
    // for every tile copy the respective tile section to the pixel buffer
    for (size_t tile_idx = 0; tile_idx < layer.tiles.size(); ++tile_idx) {
        const Tile &tile = layer.tiles[tile_idx];
        // find location of first pixel of tile
        uint32_t row, col, start_x, start_y;
        col = tile_idx % layer.width; // col in tile units
        row = tile_idx / layer.width; // row in tile units
        start_x = col * tile_width;   // x offset in pixels
        start_y = row * tile_height;  // y offset in pixels
        // get pointer to first pixel of tile
        uint32_t *pix = &pixels[start_y * layer_width_pix + start_x];
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

} // namespace omega::scene::tiled
