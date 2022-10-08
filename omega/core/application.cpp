#include "application.h"

#include "omega/util/util.h"

namespace omega::core {

using namespace omega::util;

Application *Application::current_instance = nullptr;

Application::Application(const ApplicationConfig &config) : fps(60), last_time(0), window(nullptr), running(true) {
    current_instance = this;
    window = Window::instance();
    running = window->init(config.width, config.height, config.resizable, config.title);
    // init TTF_Font
    if (TTF_Init() != 0) {
        util::log("Unable to initialize SDL_ttf: '", SDL_GetError(), "'");
        running = false;
    }
    layer_stack = create_uptr<LayerStack>();
    imgui_layer = nullptr;
    last_time = SDL_GetTicks();
}

Application::~Application() {
    delete imgui_layer;
    imgui_layer = nullptr;
    TTF_Quit();
}

void Application::push_layer(Layer *layer) {
    if (layer == nullptr) {
        log("Invalid layer: layer = nullptr!");
        return;
    }
    if (layer->is_imgui() && imgui_layer == nullptr) {
        imgui_layer = (ImGuiLayer *)layer;
        return;
    }
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
        auto input = InputManager::instance();
        input->prepare_for_update();
        Event event;
        while (input->poll_events(event)) {
            if (imgui_layer != nullptr) {
                imgui_layer->input(event);
            }
            switch ((EventType)event.type) {
            case EventType::k_quit:
                running = false;
                break;
            case EventType::k_window_event:
                if (event.window.type == (uint32_t)events::WindowEvents::k_window_resized) {
                    on_resize(event.window.data1, event.window.data2);
                }
                break;
            default:
                break;
            }
        }
        input->update();
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