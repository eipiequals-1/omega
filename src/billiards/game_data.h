#ifndef _BILLIARDS_GAME_DATA_H_
#define _BILLIARDS_GAME_DATA_H_

#include <cstdint>
#include <memory>
#include <string>

#include "libGL2D/core/using.h"
#include "libGL2D/events/input_processor.h"
#include "libGL2D/gfx/sprite_batch.h"
#include "libGL2D/gfx/texture/texture.h"

struct GameData {
	GameData() {
		sprite_batch = std::make_shared<libGL2D::SpriteBatch>();
		input = std::make_shared<libGL2D::InputProcessor>();
		texture_manager = std::make_shared<libGL2D::TextureManager>();
		running = true;
	}
	static uint32_t WIDTH;
	static uint32_t HEIGHT;
	libGL2D::Sptr<libGL2D::SpriteBatch> sprite_batch;
	libGL2D::Sptr<libGL2D::InputProcessor> input;
	libGL2D::Sptr<libGL2D::TextureManager> texture_manager;
	bool running;
};

#endif  // _BILLIARDS_GAME_DATA_H_