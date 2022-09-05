#include "application.h"

#include "omega/util/util.h"

namespace omega {

Application* Application::instance_ = nullptr;

Application::Application(const ApplicationConfig& config) : fps_(60), last_time_(0), window_(nullptr), running_(true) {
	instance_ = this;
	window_ = create_sptr<Window>();
	running_ = window_->Init(config.width, config.height, config.resizable, config.title);
	// init TTF_Font
	if (TTF_Init() != 0) {
		log("Unable to initialize SDL_ttf: '", SDL_GetError(), "'");
		running_ = false;
	}
	layer_stack_ = create_uptr<LayerStack>();
	last_time_ = SDL_GetTicks();
}

Application::~Application() {
	TTF_Quit();
}

void Application::PushLayer(Layer* layer) {
	layer_stack_->PushLayer(layer);
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
		layer_stack_->Input(dt);
		layer_stack_->Update(dt);
		layer_stack_->Render(dt);
		window_->SwapBuffers();
	}
}

void Application::OnResize(uint32_t width, uint32_t height) {
	window_->OnResize(width, height);
}

}  // namespace omega