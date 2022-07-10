#ifndef OMEGA_MAP_TILED_H
#define OMEGA_MAP_TILED_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <vector>

#include "omega/core/using.h"
#include "omega/gfx/sprite_batch.h"
#include "omega/physics/math.h"
#include "omega/vendor/map/tmxparser.h"

namespace omega {
namespace tiled {

/**
 * Stores a tiled map
 */
class Map : public TmxMap {
   public:
	Map(const std::string &file_path, const std::string &tileset_path);
	virtual ~Map();

	/**
	 * Returns if there is a collision between the surrounding rects
	 * @param rect intersection test rect
	 * @param collided_tiles vector of pointers to tiles that intersect with the given rect
	 * @param collided_tile_indices vector of ints containing the location of the collided tiles in the layer vector
	 */
	virtual void GetIntersectRects(const glm::rect &rect, std::vector<Tile *> &collided_tiles, std::vector<uint32_t> &collided_tile_indices);

	/**
	 * Sets the tile rectangle based off of the tileIdx
	 * @param rect reference to the rect to be changed
	 * @param tile_idx index of the tile in the 1d tile vector
	 */
	virtual void SetTileRect(glm::rect &rect, uint32_t tile_idx);

	/**
	 * Checks if a tile has the given property
	 * @param tile tile to check property
	 * @param property string of property to check
	 * @return out value in property map
	 * @return if the tile has the given property
	 */
	virtual bool ContainsProperty(const Tile &tile, const std::string &property, std::string &out);

	/**
	 * Finds all the tiles on the map with given property
	 * @param property the tile property to check
	 * @returns tiles_properties the vector of the tiles with that property
	 * @returns tiles_properties_idx the vector of the indices of those tiles
	 */
	virtual void GetTilesWithProperty(const std::string &property, std::vector<Tile *> &tiles_properties, std::vector<int> &tiles_properties_idx);

	/**
	 * @param x coord in tile units
	 * @param y coord in tile units
	 * @param layer coord in tile units
	 * @returns the tile at the given position
	 */
	virtual Tile &GetTileAt(int x, int y, int layer) {
		return layerCollection[layer].tiles[y * width + x];
	}

   protected:
};
}  // namespace tiled
}  // namespace omega

#endif  // OMEGA_MAP_TILED_H