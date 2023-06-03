#include "map.hpp"

#include <iostream>

namespace omega::scene::tiled {

Map::Map(const std::string &file_path, const std::string &tileset_path) {
    tmxparser::TmxReturn ret = parseFromFile(file_path, this, tileset_path);
    if (ret != tmxparser::TmxReturn::kSuccess) {
        util::error("Failed to load file: '", file_path, ".'");
    }
}

void Map::get_intersect_rects(const glm::rectf &rect,
                              std::vector<tmxparser::Tile *> &collided_tiles,
                              std::vector<u32> &collided_tile_indices) {
    // reset the output vectors
    collided_tiles.clear();
    collided_tile_indices.clear();
    // make sure that the rectangle is not out of bounds
    if (rect.x < 0.0f || rect.x + rect.w > (f32)width * tileWidth ||
        rect.y < 0.0f || rect.y + rect.h > (f32)height * tileHeight) {
        return;
    }
    // find bounds to search
    u32 left, right, top, bottom;
    left = glm::max(glm::floor(rect.x / tileWidth), 0.0f);
    right = glm::min(glm::floor((rect.x + rect.w) / tileWidth), width - 1.0f);
    bottom = glm::max(glm::floor(rect.y / tileHeight), 0.0f);
    top = glm::min(glm::floor((rect.y + rect.h) / tileHeight), height - 1.0f);
    for (auto &layer : layerCollection) {
        if (!layer.visible)
            continue;

        for (u32 y = bottom; y <= top; y++) {
            for (u32 x = left; x <= right; x++) {
                // need to flip tile_pos
                u32 tile_pos = ((layer.height - y - 1) * layer.width) + x;
                tmxparser::Tile &tile = layer.tiles[tile_pos];
                if (tile.gid != 0) {
                    collided_tiles.push_back(&tile);
                    collided_tile_indices.push_back(tile_pos);
                }
            }
        }
    }
}

void Map::set_tile_rect(glm::rectf &rect, u32 tile_idx) {
    // convert tile_idx to correct width and height
    u32 actual_x = tile_idx % width;
    u32 actual_y = height - (tile_idx / width) - 1;
    // now turn into rect
    rect.x = actual_x * tileWidth;
    rect.y = actual_y * tileHeight;
    rect.w = tileWidth;
    rect.h = tileHeight;
}

bool Map::contains_property(const tmxparser::Tile &tile,
                            const std::string &property,
                            std::string &out) {
    const tmxparser::Tileset &tileset = tilesetCollection[tile.tilesetIndex];
    const tmxparser::TileDefinitionMap_t &tile_def_map
        = tileset.tileDefinitions;
    // check if there is a definition for the tile in the tileset
    if (tile_def_map.count(tile.tileFlatIndex) == 0) {
        return false;
    }
    // check if one of the properties is the given property
    const tmxparser::TileDefinition &def = tile_def_map.at(tile.tileFlatIndex);
    if (def.propertyMap.count(property) == 0)
        return false;
    out = def.propertyMap.at(property);
    return true;
}

void Map::get_tiles_with_property(
    const std::string &property,
    std::vector<tmxparser::Tile *> &tiles_properties,
    std::vector<int> &tiles_properties_idx) {
    tiles_properties.clear();
    tiles_properties_idx.clear();
    for (auto &layer : layerCollection) {
        // if (!layer.visible) continue;
        auto &tiles = layer.tiles;
        // check all tiles in current layer
        // for the property
        for (size_t tile_gid = 0; tile_gid < tiles.size(); ++tile_gid) {
            auto &tile = tiles[tile_gid];
            if (tile.gid == 0)
                continue;
            // check if the tile has the property
            std::string out;
            if (contains_property(tile, property, out)) {
                tiles_properties.push_back(&tile);
                tiles_properties_idx.push_back(tile_gid);
            }
        }
    }
}

} // namespace omega::scene::tiled
