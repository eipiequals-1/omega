#include "application.h"

#include "libGL2D/physics/math.h"

namespace libgl {
Application::Application(const ApplicationConfig& config) : fps_(60), last_time_(0), window_(nullptr), running_(true) {
	window_ = CreateUptr<Window>();
	running_ = window_->Init(config.width, config.height, config.resizable, config.title);
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
		switch ((EventType)event.type) {
		case EventType::kQuit: {
			running_ = false;
			break;
		}
		case EventType::kWindowEvent: {
			if (event.window.type == (uint32_t)WindowEvents::kWindowResized) {
				OnResize(event.window.data1, event.window.data2);
			}
			break;
		}
		default:
			break;
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

void Application::OnResize(uint32_t width, uint32_t height) {
	window_->OnResize(width, height);
}

}  // namespace libgl