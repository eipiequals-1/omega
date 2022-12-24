#include "application.h"

#include "omega/util/util.h"

namespace omega::core {

Application *Application::current_instance = nullptr;

Application::Application(const ApplicationConfig &config) : fps(60), last_time(0), window(nullptr), running(true) {
    current_instance = this;
    window = Window::instance();
    running = window->init(config.width, config.height, config.resizable, config.title);
    // init TTF_Font
    if (TTF_Init() != 0) {
        util::error("Unable to initialize SDL_ttf: '", SDL_GetError(), "'");
        running = false;
    }
    layer_stack = create_uptr<LayerStack>();
    imgui_layer = nullptr;
    Time::init();
    last_time = Time::get_time_millis<float>();
}

Application::~Application() {
    delete imgui_layer;
    imgui_layer = nullptr;
    TTF_Quit();
}

void Application::push_layer(Layer *layer) {
    if (layer == nullptr) {
        error("Invalid layer: layer = nullptr!");
        return;
    }
    if (layer->is_imgui() && imgui_layer == nullptr) {
        imgui_layer = (ImGuiLayer *)layer;
        return;
    }
    layer_stack->push_layer(layer);
}

float Application::tick() {
    Time::sleep(glm::max(1000.0f / fps - (float)(Time::get_time_millis<float>() - last_time) * 1000.0f, 0.0f));
    // SDL_Delay();
    float current_time = Time::get_time_millis<float>();
    float dt = (current_time - last_time) / 1000.0f; // convert to seconds
    last_time = current_time;
    return dt;
}

void Application::run() {
    while (running) {
        float dt = tick();
        auto input = InputManager::instance();
        input->prepare_for_update();
        Event event;
        while (input->poll_events(event)) {
            if (imgui_layer != nullptr) {
                imgui_layer->input(event);
            }
            switch ((EventType)event.type) {
            case EventType::quit:
                running = false;
                break;
            case EventType::window_event:
                if (event.window.event == (uint32_t)events::WindowEvents::window_resized) {
                    on_resize(event.window.data1, event.window.data2);
                }
                break;
            default:
                break;
            }
        }
        input->update();
        // handle the inputs to the layers
        layer_stack->input(dt);
        if (imgui_layer != nullptr) {
            imgui_layer->input(dt);
        }

        // update the layers and timers
        Time::tick(dt);
        layer_stack->update(dt);
        if (imgui_layer != nullptr) {
            imgui_layer->update(dt);
        }

        // render each layer
        layer_stack->render(dt);
        if (imgui_layer != nullptr) {
            imgui_layer->render(dt);
        }

        window->swap_buffers();
    }
}

void Application::on_resize(uint32_t width, uint32_t height) {
    window->on_resize(width, height);
}

} // namespace omega::core