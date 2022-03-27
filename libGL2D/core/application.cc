#include "application.h"

#include "libGL2D/physics/math.h"
namespace libgl {
Application::Application(const WinBuilder& builder) : running_(true), fps_(60) {
	window_ = std::make_unique<Window>();
	running_ = window_->Init(builder);
	last_time_ = SDL_GetTicks();
}

Application::~Application() {
}

void Application::Update(float dt) {
	(void)dt;
}

void Application::Input(float dt) {
	(void)dt;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running_ = false;
		}
	}
}

void Application::Render(float dt) {
	(void)dt;
}

float Application::Tick() {
	SDL_Delay(glm::max(1000.0f / fps_ - (SDL_GetTicks() - last_time_), 0.0f));
	uint32_t current_time = SDL_GetTicks();
	float dt = (current_time - last_time_) / 1000.0f;  // convert to seconds
	last_time_ = current_time;
	return dt;
}

void Application::Run() {
	while (running_) {
		float dt = Tick();
		Input(dt);
		Update(dt);
		Render(dt);
		window_->SwapBuffers();
	}
}
}