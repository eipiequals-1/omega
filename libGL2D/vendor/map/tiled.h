#ifndef _LIBTMX_PARSER_TILED_H_
#define _LIBTMX_PARSER_TILED_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <vector>

#include "libGL2D/core/using.h"
#include "libGL2D/gfx/sprite_batch.h"
#include "libGL2D/physics/math.h"
#include "libGL2D/vendor/map/tmxparser.h"

namespace libgl {
namespace tiled {

class Map : private TmxMap {
   public:
	Map(const std::string &file_path, const std::string &tileset_path);
	virtual ~Map();
	/**
	 * Render Map
	 * @param batch to draw
	 */
	virtual void Render(SpriteBatch &batch);

	/**
	 * Returns if there is a collision between the surrounding rects
	 * @param rect intersection test rect
	 * @param collidedRects vector of pointers to tiles that intersect with the given rect
	 * @param collidedTileIndices vector of ints containing the location of the collided tiles in the layer vector
	 * @return if the given rect collides with any non empty tiles
	 */
	virtual bool GetIntersectRects(glm::rect &rect, std::vector<Tile *> &collided_tiles, std::vector<int> &collided_tile_indices);

	/**
	 * Sets the tile rectangle based off of the tileIdx
	 * @param rect reference to the rect to be changed
	 * @param tileIdx index of the tile in the 1d tile vector
	 */
	virtual void SetTileRect(glm::rect &rect, unsigned int tile_idx);

	/**
	 * Checks if a tile has the given property
	 * @param tile tile to check property
	 * @param property string of property to check
	 * @param out value in property map
	 * @return if the tile has the given property
	 * */
	virtual bool ContainsProperty(const Tile &tile, const std::string &property, std::string &out);

	virtual void GetTilesWithProperty(const std::string &property, std::vector<Tile *> &tiles_properties, std::vector<int> &tiles_properties_idx);

	virtual Tile &GetTileAt(int x, int y, int layer) {
		return layerCollection[layer].tiles[y * width + x];
	}

   protected:
	virtual void RenderTileLayer(SpriteBatch &batch, const Layer &layer);
	virtual void RenderObjectLayer(SpriteBatch &batch, const Layer &layer);
	// virtual void RenderImageLayer(SDL_Renderer *renderer);

	// used for drawing and collisions
	Uptr<TextureManager> tex_manager_;
};
}  // namespace tiled
}  // namespace libgl

#endif  // _LIBTMX_PARSER_TILED_H_