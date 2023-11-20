#include "map_renderer.hpp"

#include "omega/math/math.hpp"
#include "omega/scene/orthographic_camera.hpp"

namespace omega::scene::tiled {

MapRenderer::MapRenderer(Map *map, const std::string &tileset_path) : map(map) {
    std::string path;

    for (size_t i = 0; i < map->tilesetCollection.size(); ++i) {
        const auto &tileset = map->tilesetCollection[i];
        path = tileset.image.source;
        tileset_textures.push_back(
            gfx::texture::Texture::create_from_file(tileset_path + "/" + path));
    }
}

MapRenderer::~MapRenderer() {
    for (auto &layer : layers) {
        delete layer;
        layer = nullptr;
    }
}

void MapRenderer::setup(gfx::SpriteBatch &sprite_batch) {
    u32 tile_width = map->tileWidth;
    u32 tile_height = map->tileHeight;
    u32 layer_width_pix = tile_width * map->width;
    u32 layer_height_pix = tile_height * map->height;
    OrthographicCamera camera(0.0f, layer_width_pix,
                              0.0f, layer_height_pix);

    camera.recalculate_view_matrix();
    sprite_batch.set_view_projection_matrix(
        camera.get_view_projection_matrix());
    
    for (u32 i = 0; i < map->layerCollection.size(); ++i) {
        layers.push_back(
            new gfx::FrameBuffer(
                layer_width_pix, layer_height_pix,
                {
                    {
                     .width = layer_width_pix,
                     .height = layer_height_pix,
                     .name = "color_buffer", 
                     .min_filter = gfx::TextureParam::NEAREST,
                     .mag_filter = gfx::TextureParam::NEAREST}
                }
            )
        );
    }

    for (u32 z = 0; z < map->layerCollection.size(); ++z) {
        tmxparser::Layer &layer = map->layerCollection[z];
        auto &framebuffer = layers[z];
        framebuffer->bind();

        sprite_batch.begin_render();
        for (size_t tile_idx = 0; tile_idx < layer.tiles.size(); ++tile_idx) {
            const tmxparser::Tile &tile = layer.tiles[tile_idx];
            const tmxparser::Tileset &tileset = map->tilesetCollection[tile.tilesetIndex];
            // find location of first pixel of tile
            u32 row, col, start_x, start_y;
            col = tile_idx % layer.width; // col in tile units
            row = tile_idx / layer.width; // row in tile units
            start_x = col * tile_width;   // x offset in pixels
            start_y = row * tile_height;  // y offset in pixels
            
            if (tile.gid == 0) {continue;}
            u32 gid = tile.tileFlatIndex;
            math::rectf src(
                (gid % tileset.colCount) * tileset.tileWidth,
                ((int)(gid / tileset.colCount) + 1) * tileset.tileHeight,
                tileset.tileWidth,
                -(float)(tileset.tileHeight)
            );
            math::rectf dest(start_x, start_y, tile_width, tile_height);
            sprite_batch.render_texture(tileset_textures[0].get(), src, dest);
        }
        sprite_batch.end_render();
        framebuffer->unbind();
    }
}

void MapRenderer::render(gfx::SpriteBatch &batch) {
    for (u32 z = 0; z < map->layerCollection.size(); ++z) {
        auto &layer = map->layerCollection[z];
        if (layer.visible) {
            auto &attach = layers[z]->get_attachment("color_buffer");
            auto texture_wrapper = gfx::texture::Texture::create_wrapper(
                attach.id, attach.width, attach.height);
            batch.render_texture(texture_wrapper.get(), 0.0f, 0.0f);
        }
    }
}

} // namespace omega::scene::tiled
