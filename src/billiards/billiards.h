#ifndef _BILLIARDS_BILLIARDS_H_
#define _BILLIARDS_BILLIARDS_H_

#include "billiards/game_data.h"
#include "billiards/gamescreen.h"
#include "libGL2D/core/application.h"
#include "libGL2D/core/using.h"
#include "libGL2D/gfx/texture/texture.h"

class Billiards : public libGL2D::Application {
   public:
	Billiards();
	~Billiards() override;

	void Run() override;
	void Render(float dt) override;
	void Update(float dt) override;
	void Input(float dt) override;

	libGL2D::Sptr<GameData> game_data() { return game_data_; }

   private:
	libGL2D::Uptr<GameScreen> game_screen_;
	libGL2D::Sptr<GameData> game_data_;
};

#endif  // _BILLIARDS_BILLIARDS_H_