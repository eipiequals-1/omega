#include "application.h"

#include "omega/util/util.h"

namespace omega::core {

using namespace omega::util;

Application *Application::current_instance = nullptr;

Application::Application(const ApplicationConfig &config) : fps(60), last_time(0), window(nullptr), running(true) {
    current_instance = this;
    window = create_sptr<Window>();
    running = window->init(config.width, config.height, config.resizable, config.title);
    // init TTF_Font
    if (TTF_Init() != 0) {
        util::log("Unable to initialize SDL_ttf: '", SDL_GetError(), "'");
        running = false;
    }
    layer_stack = create_uptr<LayerStack>();
    last_time = SDL_GetTicks();
}

Application::~Application() {
    TTF_Quit();
}

void Application::push_layer(Layer *layer) {
    layer_stack->push_layer(layer);
}

f32 Application::tick() {
    SDL_Delay(glm::max(1000.0f / fps - (SDL_GetTicks() - last_time), 0.0f));
    u32 current_time = SDL_GetTicks();
    f32 dt = (current_time - last_time) / 1000.0f; // convert to seconds
    last_time = current_time;
    return dt;
}

void Application::run() {
    while (running) {
        f32 dt = tick();
        layer_stack->input(dt);
        layer_stack->update(dt);
        layer_stack->render(dt);
        window->swap_buffers();
    }
}

void Application::on_resize(u32 width, u32 height) {
    window->on_resize(width, height);
}

} // namespace omega::core