#include "tiled.h"

#include <iostream>

namespace omega {
namespace tiled {

Map::Map(const std::string &file_path, const std::string &tileset_path) {
	TmxReturn ret = parseFromFile(file_path, this, tileset_path);
	if (ret != TmxReturn::kSuccess) {
		Log("Failed to load file: '", file_path, ".'");
	}
}

Map::~Map() {
}

void Map::GetIntersectRects(const glm::rect &rect, std::vector<Tile *> &collided_tiles, std::vector<uint32_t> &collided_tile_indices) {
	// reset the output vectors
	collided_tiles.clear();
	collided_tile_indices.clear();
	// find bounds to search
	uint32_t left, right, top, bottom;
	left = glm::max(glm::floor(rect.x / tileWidth), 0.0f);
	right = glm::min(glm::floor((rect.x + rect.w) / tileWidth), width - 1.0f);
	bottom = glm::max(glm::floor(rect.y / tileHeight), 0.0f);
	top = glm::min(glm::floor((rect.y + rect.h) / tileHeight), height - 1.0f);
	for (auto &layer : layerCollection) {
		if (!layer.visible) continue;

		for (uint32_t y = bottom; y <= top; y++) {
			for (uint32_t x = left; x <= right; x++) {
				// need to flip tile_pos
				uint32_t tile_pos = ((layer.height - y - 1) * layer.width) + x;
				Tile &tile = layer.tiles[tile_pos];
				if (tile.gid != 0) {
					collided_tiles.push_back(&tile);
					collided_tile_indices.push_back(tile_pos);
				}
			}
		}
	}
}

void Map::SetTileRect(glm::rect &rect, uint32_t tile_idx) {
	// convert tile_idx to correct width and height
	uint32_t actual_x = tile_idx % width;
	uint32_t actual_y = height - (tile_idx / width) - 1;
	// now turn into rect
	rect.x = actual_x * tileWidth;
	rect.y = actual_y * tileHeight;
	rect.w = tileWidth;
	rect.h = tileHeight;
}

bool Map::ContainsProperty(const Tile &tile, const std::string &property, std::string &out) {
	const Tileset &tileset = tilesetCollection[tile.tilesetIndex];
	const TileDefinitionMap_t &tile_def_map = tileset.tileDefinitions;
	// check if there is a definition for the tile in the tileset
	if (tile_def_map.count(tile.tileFlatIndex) == 0) {
		return false;
	}
	// check if one of the properties is the given property
	const TileDefinition &def = tile_def_map.at(tile.tileFlatIndex);
	if (def.propertyMap.count(property) == 0) return false;
	out = def.propertyMap.at(property);
	return true;
}

void Map::GetTilesWithProperty(const std::string &property, std::vector<Tile *> &tiles_properties, std::vector<int> &tiles_properties_idx) {
	tiles_properties.clear();
	tiles_properties_idx.clear();
	for (auto &layer : layerCollection) {
		// if (!layer.visible) continue;
		auto &tiles = layer.tiles;
		// check all tiles in current layer
		// for the property
		for (size_t tile_gid = 0; tile_gid < tiles.size(); ++tile_gid) {
			auto &tile = tiles[tile_gid];
			if (tile.gid == 0) continue;
			// check if the tile has the property
			std::string out;
			if (ContainsProperty(tile, property, out)) {
				tiles_properties.push_back(&tile);
				tiles_properties_idx.push_back(tile_gid);
			}
		}
	}
}

}  // namespace tiled
}  // namespace omega