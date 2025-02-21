#ifndef OMEGA_SCENE_TILED_MAP_HPP
#define OMEGA_SCENE_TILED_MAP_HPP

#include <libtmx-parser/tmxparser.h>

#include <string>
#include <vector>

#include "omega/gfx/sprite_batch.hpp"
#include "omega/math/math.hpp"
#include "omega/util/std.hpp"
#include "omega/util/types.hpp"

namespace omega::scene::tiled {

/**
 * Stores a tiled map
 */
class Map : public tmxparser::TmxMap {
  public:
    Map(const std::string &file_path, const std::string &tileset_path);
    virtual ~Map() = default;

    /**
     * Returns if there is a collision between the surrounding rects
     * @param rect intersection test rect
     * @param collided_tiles vector of pointers to tiles that intersect
     * with the given rect
     * @param collided_tile_indices vector of ints containing the location
     * of the collided tiles in the layer vector
     */
    void get_intersect_rects(const math::rectf &rect,
                             std::vector<tmxparser::Tile *> &collided_tiles,
                             std::vector<u32> &collided_tile_indices);

    /**
     * Returns if there is a collision between the surrounding rects
     * @param rect intersection test rect
     * @param collided_tiles vector of pointers to tiles that intersect
     * with the given rect
     * @param collided_tile_indices vector of ints containing the location
     * of the collided tiles in the layer vector
     * @param func a function that returns whether or not the tile should be
     * counted (i.e. return false if it should be passed through)
     */

    void get_intersect_rects(const math::rectf &rect,
                             std::vector<tmxparser::Tile *> &collided_tiles,
                             std::vector<u32> &collided_tile_indices,
                             std::function<bool(tmxparser::Tile *, u32)> func);

    /**
     * Sets the tile rectangle based off of the tileIdx
     * @param rect reference to the rect to be changed
     * @param tile_idx index of the tile in the 1d tile vector
     */
    virtual void set_tile_rect(math::rectf &rect, u32 tile_idx);

    /**
     * Checks if a tile has the given property
     * @param tile tile to check property
     * @param property string of property to check
     * @return out value in property map
     * @return if the tile has the given property
     */
    virtual bool contains_property(const tmxparser::Tile &tile,
                                   const std::string &property,
                                   std::string &out);

    /**
     * Finds all the tiles on the map with given property
     * @param property the tile property to check
     * @returns tiles_properties the vector of the tiles with that property
     * @returns tiles_properties_idx the vector of the indices of those tiles
     */
    virtual void get_tiles_with_property(
        const std::string &property,
        std::vector<tmxparser::Tile *> &tiles_properties,
        std::vector<i32> &tiles_properties_idx);

    /**
     * @param x coord in tile units
     * @param y coord in tile units
     * @param layer coord in tile units
     * @returns the tile at the given position
     */
    virtual tmxparser::Tile &get_tile_at(i32 x, i32 y, i32 layer) {
        return layerCollection[layer].tiles[y * width + x];
    }
};
} // namespace omega::scene::tiled

#endif // OMEGA_SCENE_TILED_MAP_HPP
