#include "tiled.h"

#include <iostream>

namespace libGL2D {
namespace tiled {

Map::Map(const std::string &file_path, const std::string &tileset_path) {
	TmxReturn ret = parseFromFile(file_path, this, tileset_path);
	if (ret != TmxReturn::kSuccess) {
		std::cout << "Failed to load file: '" << file_path << "'.\n";
	}
	for (const auto &tileset : tilesetCollection) {
		std::string path = tileset.source;
		tex_manager_->Load(tileset.name, path);
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
	glm::rect src, dest;
	for (size_t tile_idx = 0; tile_idx < layer.tiles.size(); ++tile_idx) {
		const auto &tile = layer.tiles[tile_idx];
		if (tile.gid == 0) continue;
		const Tileset &tileset = tilesetCollection[tile.tilesetIndex];
		// tileset pos
		src.x = tileset.tileMarginInImage + (tileset.tileSpacingInImage + tileset.tileWidth) * (tile.tileFlatIndex % tileset.colCount);
		src.y = tileset.tileMarginInImage + (tileset.tileSpacingInImage + tileset.tileHeight) * (tile.tileFlatIndex / tileset.colCount);
		src.w = tileset.tileWidth;
		src.h = tileset.tileHeight;
		dest.x = (tile_idx % width) * tileWidth;
		dest.y = (tile_idx / width) * tileHeight;
		dest.w = tileWidth;
		dest.h = tileHeight;
		batch.RenderTexture(tex_manager_->Get(tileset.name).get(), src, dest);
	}
}

}  // namespace tiled
}  // namespace libGL2D