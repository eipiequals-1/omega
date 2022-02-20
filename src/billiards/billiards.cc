#include "billiards.h"

#include <GL/gl.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "billiards/game_data.h"

Billiards::Billiards() : libGL2D::Application::Application({GameData::WIDTH, GameData::HEIGHT, "Billiards v. 0.0.4", SDL_WINDOW_OPENGL, SDL_INIT_VIDEO}), game_data_(nullptr) {
	if (TTF_Init() != 0) {
		std::cout << "Failed to initialize SDL2_ttf" << std::endl;
	}
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	game_data_ = std::make_shared<GameData>();
	game_data_->running = running_;

	auto texture_manager = game_data_->texture_manager;
	texture_manager->Load("pool_table", "./res/gfx/pool_table.png");
	texture_manager->Load("white_ball", "./res/gfx/white_ball.png");
	texture_manager->Load("yellow_ball", "./res/gfx/yellow_ball.png");
	texture_manager->Load("red_ball", "./res/gfx/red_ball.png");
	texture_manager->Load("stick", "./res/gfx/stick.png");

	game_screen_ = std::make_unique<GameScreen>(game_data_.get());
}

Billiards::~Billiards() {
	TTF_Quit();
}

void Billiards::Run() {
	while (game_data_->running) {
		float dt = Tick();
		Input(dt);
		Update(dt);
		window_->Clear();
		Render(dt);
		window_->SwapBuffers();
	}
}

void Billiards::Render(float dt) {
	game_screen_->Render(dt);
}

void Billiards::Input(float dt) {
	game_screen_->Input(dt);
}

void Billiards::Update(float dt) {
	game_screen_->Update(dt);
}
