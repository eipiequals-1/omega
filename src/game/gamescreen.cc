#include "gamescreen.h"

#include <GL/gl.h>
#include <SDL2/SDL.h>

#include <iostream>

GameScreen::GameScreen(GameData* game_data) : game_data_(game_data) {
	proj_matrix_ = glm::ortho(0.0f, (float)game_data_->WIDTH, 0.0f, (float)game_data_->HEIGHT, -1.0f, 1.0f);
	game_data_->sprite_batch->SetViewProjectionMatrix(proj_matrix_);

	ball_ = std::make_unique<Ball>(game_data_->texture_manager->Get("white_ball"), game_data_->WIDTH / 2.0f, game_data_->HEIGHT / 2.0f, Ball::RADIUS);
	table_ = std::make_unique<Table>(game_data_->texture_manager.get(), game_data_->WIDTH, game_data_->HEIGHT);

	const glm::rect table_rect = table_->GetCollisionRect();
	libGL2D::Sptr<libGL2D::Texture> yellow_ball = game_data_->texture_manager->Get("yellow_ball");
	libGL2D::Sptr<libGL2D::Texture> red_ball = game_data_->texture_manager->Get("red_ball");

	const float ballDiameter = Ball::RADIUS * 2.0f;
	glm::vec2 spawn = glm::vec2(table_rect.x + table_rect.w * 0.75f, table_rect.y + table_rect.h * 0.5f);
	// offset start spawn by 2 balls
	spawn.x -= ballDiameter * 2.0f;
	for (int i = 1; i <= 4; i++) {
		// calculate x coord based off of 3/4 table
		float x = spawn.x + ballDiameter * (i - 1);  // left x
		x += Ball::RADIUS;                           // center x
		float y;
		float colH = i * ballDiameter;
		for (int numBalls = 1; numBalls <= i; numBalls++) {
			y = spawn.y - colH / 2.0f + ballDiameter * (numBalls - 1);  // bottom y
			y += Ball::RADIUS;                                          // center y
			// choose ball color
			if (other_balls_.size() % 2 == 0) {
				other_balls_.push_back(std::make_unique<Ball>(yellow_ball, x, y, Ball::RADIUS));
			} else {
				other_balls_.push_back(std::make_unique<Ball>(red_ball, x, y, Ball::RADIUS));
			}
		}
	}
	holes_.push_back(std::make_unique<Hole>(70 + table_->get_rect().x, 70 + table_->get_rect().y, 30));
}

GameScreen::~GameScreen() {
}

void GameScreen::Render(float dt) {
	(void)dt;

	auto sprite_batch = game_data_->sprite_batch;
	sprite_batch->BeginRender();

	table_->Render(*sprite_batch);
	ball_->Render(*sprite_batch);

	for (auto& b : other_balls_) {
		b->Render(*sprite_batch);
	}
	// render hud
	sprite_batch->Render(game_data_->WIDTH * 0.0225f, game_data_->HEIGHT * 0.2f, game_data_->WIDTH * 0.05f, game_data_->HEIGHT * 0.6f, glm::vec4(0.0f, 0.1f, 0.1f, 1.0f));
	sprite_batch->Render(game_data_->WIDTH * 0.0225f, game_data_->HEIGHT * 0.2f, game_data_->WIDTH * 0.05f, game_data_->WIDTH * 0.6f * ball_->GetChargePercent(), glm::vec4(1.0f, 1.0f, 0.1f, 1.0f));
	// debug
	// glm::vec2 mousePos = game->GetInputProcessor()->GetMousePos();
	// mousePos.y = game->GetHeight() - mousePos.y;
	// spriteBatch->Render(game->GetTextureManager()->Get("stick").get(), mousePos.x, mousePos.y, 938.0f, 22.0f, glm::vec2(0.0f, 10.0f), 100.0f, {0.7f, 0.7f, 1.0f, 1.0f});

	sprite_batch->EndRender();
}

void GameScreen::Update(float dt) {
	ball_->Update(dt);

	ball_->CheckBounds(table_->GetCollisionRect());
	// hole collision
	for (auto holeItr = holes_.begin(); holeItr != holes_.end(); ++holeItr) {
		Hole& hole = **holeItr;
		if (hole.IsBallIn(ball_->get_rect().center(), Ball::RADIUS)) {
			ball_->SetCenter(game_data_->WIDTH / 2.0f, game_data_->HEIGHT / 2.0f);
			ball_->set_vel({0.0f, 0.0f});
		}
	}

	// collisions with main ball
	for (auto itr = other_balls_.begin(); itr != other_balls_.end(); ++itr) {
		Ball& b = **itr;
		b.Update(dt);
		b.CheckBounds(table_->GetCollisionRect());
		const glm::rect& rect = b.get_rect();
		if (glm::circleVsCircle(rect.center(), Ball::RADIUS, ball_->get_rect().center(), Ball::RADIUS)) {
			ball_->OnBallCollision(b, dt);
		}
		// hole collision
		for (auto holeItr = holes_.begin(); holeItr != holes_.end(); ++holeItr) {
			Hole& hole = **holeItr;
			if (hole.IsBallIn(b.get_rect().center(), Ball::RADIUS)) {
				b.SetInHole(true);
			}
		}
	}
	for (auto itr = other_balls_.begin(); itr != other_balls_.end(); ++itr) {
		Ball& b1 = **itr;
		const glm::rect& rect1 = b1.get_rect();
		// dont need to check balls before
		for (auto secondItr = itr + 1; secondItr != other_balls_.end(); ++secondItr) {
			Ball& b2 = **secondItr;
			const glm::rect& rect2 = b2.get_rect();
			// check if it's not itself
			if (rect1 == rect2) continue;
			if (glm::circleVsCircle(rect1.center(), Ball::RADIUS, rect2.center(), Ball::RADIUS)) {
				b1.OnBallCollision(b2, dt);
			}
		}
	}
}

void GameScreen::Input(float dt) {
	game_data_->input->PrepareForUpdate();
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			game_data_->running = false;
			break;
		}
	}
	game_data_->input->Update();
	if (game_data_->input->GetKeyProcessor().KeyJustPressed(SDL_SCANCODE_ESCAPE)) {
		game_data_->running = false;
	}
	ball_->Input(*game_data_->input, dt);
}
