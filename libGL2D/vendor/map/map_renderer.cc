#include "map_renderer.h"

namespace libgl {
namespace tiled {

MapRenderer::MapRenderer(Map *map, const std::string &tileset_path) : map_(map) {
	std::string path;
	tex_manager_ = std::make_unique<TextureManager<uint32_t>>();
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
	uint32_t rmask, gmask, bmask, amask;
	if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	} else {
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	}

	SDL_Surface *surf = SDL_CreateRGBSurfaceFrom(pixels.data(), layer_width_pix, layer_height_pix, 32, layer_width_pix * 4, rmask, gmask, bmask, amask);
	layer_texture_.push_back(std::make_unique<Texture>(surf));
}

void MapRenderer::Render(SpriteBatch &batch) {
	// (void)batch;
	for (const auto &layer : layer_texture_) {
		batch.RenderTexture(layer.get(), 0.0f, 0.0f);
	}
}

void MapRenderer::RenderTileLayer(SpriteBatch &batch, const Layer &layer) {
	(void)batch;
	(void)layer;
}

}  // namespace tiled
}  // namespace libgl