#include "application.h"

#include "libGL2D/physics/math.h"

namespace libgl {
Application::Application(const WinBuilder& builder) : fps_(60), last_time_(0), window_(nullptr), running_(true) {
	window_ = CreateUptr<Window>();
	running_ = window_->Init(builder);
	// init TTF_Font
	if (TTF_Init() != 0) {
		libgl::Log("Unable to initialize SDL_ttf: '", SDL_GetError(), "'");
		running_ = false;
	}
	last_time_ = SDL_GetTicks();
}

Application::~Application() {
	TTF_Quit();
}

void Application::Update(float dt) {
	(void)dt;
}

void Application::Input(float dt) {
	(void)dt;
	Event event;
	while (InputManager::Instance().PollEvents(event)) {
		if ((EventType)event.type == EventType::kQuit) {
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

void Application::OnResize(const Event& event) {
	if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
		window_->OnResize(event.window.data1, event.window.data2);
	}
}

}  // namespace libgl