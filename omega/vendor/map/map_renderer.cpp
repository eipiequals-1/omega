#include "map_renderer.h"

namespace omega {
namespace tiled {

MapRenderer::MapRenderer(Map *map, const std::string &tileset_path) : map_(map) {
	std::string path;
	tex_manager_ = CreateUptr<TextureManager<uint32_t>>();
	for (size_t i = 0; i < map_->tilesetCollection.size(); ++i) {
		const auto &tileset = map_->tilesetCollection[i];
		path = tileset.image.source;
		tex_manager_->Load(i, tileset_path + "/" + path, GL_NEAREST, GL_NEAREST);
	}
	// create new texture per layer
	for (const auto &layer : map_->layerCollection) {
		if (layer.visible) {
			LoadLayer(layer);
		}
	}
}

MapRenderer::~MapRenderer() {
}

void MapRenderer::LoadLayer(const Layer &layer) {
	uint32_t tile_width = map_->tileWidth;
	uint32_t tile_height = map_->tileHeight;
	uint32_t layer_width_pix = tile_width * layer.width;
	uint32_t layer_height_pix = tile_height * layer.height;
	// use uint32_t for each pixel
	// 1 byte / color component
	uint32_t num_pixels = layer_width_pix * layer_height_pix;  // allocate area of all pixels
	std::vector<uint32_t> pixels;
	pixels.resize(num_pixels);
	// for every tile copy the respective tile section to the pixel buffer
	for (size_t tile_idx = 0; tile_idx < layer.tiles.size(); ++tile_idx) {
		const Tile &tile = layer.tiles[tile_idx];
		// find location of first pixel of tile
		uint32_t row, col, start_x, start_y;
		col = tile_idx % layer.width;  // col in tile units
		row = tile_idx / layer.width;  // row in tile units
		start_x = col * tile_width;    // x offset in pixels
		start_y = row * tile_height;   // y offset in pixels
		// get pointer to first pixel of tile
		uint32_t *pix = &pixels[start_y * layer_width_pix + start_x];
		SetTilePixels(pix, tile, layer_width_pix, layer_height_pix);
	}
	layer_texture_.push_back(Texture::CreateEmpty(layer_width_pix, layer_height_pix, GL_NEAREST, GL_NEAREST));
	(layer_texture_.end() - 1)->get()->SetData(pixels.data());
}

void MapRenderer::Render(SpriteBatch &batch) {
	for (const auto &layer : layer_texture_) {
		batch.RenderTexture(layer.get(), 0.0f, 0.0f);
	}
}

}  // namespace tiled
}  // namespace omega