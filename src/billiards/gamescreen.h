#ifndef _BILLIARDS_GAMESCREEN_H_
#define _BILLIARDS_GAMESCREEN_H_

#include <vector>

#include "billiards/entity/ball.h"
#include "billiards/entity/hole.h"
#include "billiards/entity/table.h"
#include "billiards/game_data.h"
#include "libGL2D/core/using.h"
#include "libGL2D/gfx/sprite_batch.h"
#include "libGL2D/physics/math.h"
#include "libGL2D/physics/random.h"

class GameScreen {
   public:
	explicit GameScreen(GameData *game_data);
	~GameScreen();
	void Render(float dt);
	void Update(float dt);
	void Input(float dt);

   private:
	// entities
	libGL2D::Uptr<Ball> ball_;
	libGL2D::Uptr<Table> table_;
	std::vector<libGL2D::Uptr<Ball>> other_balls_;
	std::vector<libGL2D::Uptr<Hole>> holes_;

	glm::mat4 proj_matrix_;
	GameData *game_data_;

	// Uptr<Font> font;
	// Uptr<Texture> tex;
};

#endif  // _BILLIARDS_GAMESCREEN_H_