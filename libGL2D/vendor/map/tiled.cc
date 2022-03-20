#include "tiled.h"

#include <iostream>

namespace libGL2D {
namespace tiled {

Map::Map(const std::string &file_path, const std::string &tileset_path) {
	TmxReturn ret = parseFromFile(file_path, this, tileset_path);
	if (ret != TmxReturn::kSuccess) {
		std::cout << "Failed to load file: '" << file_path << "'.\n";
	}
	std::string path;
	tex_manager_ = std::make_unique<TextureManager>();
	for (const auto &tileset : tilesetCollection) {
		path = tileset.image.source;
		tex_manager_->Load(tileset.name, path, GL_NEAREST, GL_NEAREST);
	}
}

Map::~Map() {
}

void Map::Render(SpriteBatch &batch) {
	for (const auto &layer : layerCollection) {
		if (layer.visible) {
			RenderTileLayer(batch, layer);
		}
	}
}

void Map::RenderTileLayer(SpriteBatch &batch, const Layer &layer) {
	auto img = tex_manager_->Get("tileset").get();
	glm::rect src, dest;
	batch.RenderTexture(img, src, dest);
	for (size_t tile_idx = 0; tile_idx < layer.tiles.size(); ++tile_idx) {
		const auto &tile = layer.tiles[tile_idx];
		if (tile.gid == 0) {
			continue;
		}
		const auto &tileset = tilesetCollection[tile.tilesetIndex];
		uint32_t x = tile.tileFlatIndex % tileset.colCount;
		uint32_t y = tileset.rowCount - 1 - tile.tileFlatIndex / tileset.colCount;  // invert y
		src.w = tileset.tileWidth;
		src.h = tileset.tileHeight;
		src.x = x * src.w;
		src.y = y * src.h;
		// invert y as well
		dest.x = (tile_idx % width) * tileWidth;
		dest.y = (height - 1 - tile_idx / width) * tileHeight;
		dest.w = tileWidth;
		dest.h = tileHeight;

		batch.RenderTexture(img, src, dest, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	}
}

void Map::RenderObjectLayer(SpriteBatch &batch, const Layer &layer) {
	(void)batch;
	(void)layer;
}

bool Map::GetIntersectRects(glm::rect &rect, std::vector<Tile *> &collided_tiles, std::vector<int> &collided_tile_indices) {
	(void)rect;
	(void)collided_tiles;
	(void)collided_tile_indices;
	return false;
}

void Map::SetTileRect(glm::rect &rect, unsigned int tile_idx) {
	(void)rect;
	(void)tile_idx;
}

bool Map::ContainsProperty(const Tile &tile, const std::string &property, std::string &out) {
	(void)tile;
	(void)property;
	(void)out;
	return false;
}

void Map::GetTilesWithProperty(const std::string &property, std::vector<Tile *> &tiles_properties, std::vector<int> &tiles_properties_idx) {
	(void)property;
	(void)tiles_properties;
	(void)tiles_properties_idx;
}

}  // namespace tiled
}  // namespace libGL2D