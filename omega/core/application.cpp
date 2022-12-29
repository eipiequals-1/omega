#include "application.h"

#include "omega/util/log.h"
#include "omega/util/math.h"
#include "omega/util/time.h"

namespace omega::core {

Application *Application::current_instance = nullptr;

Application::Application(const ApplicationConfig &config) {
    current_instance = this;
    window = Window::instance();
    running = window->init(config.width, config.height, config.resizable, config.title);
    // init TTF_Font
    if (TTF_Init() != 0) {
        util::error("Unable to initialize SDL_ttf: '", SDL_GetError(), "'");
        running = false;
    }
    layer_stack = util::create_uptr<scene::LayerStack>();
    util::Time::init();
    last_time = util::Time::get_time<float>();
}

Application::~Application() {
    delete imgui_layer;
    imgui_layer = nullptr;
    TTF_Quit();
}

void Application::push_layer(scene::Layer *layer) {
    if (layer == nullptr) {
        util::error("Invalid layer: layer = nullptr!");
        return;
    }
    if (layer->is_imgui() && imgui_layer == nullptr) {
        imgui_layer = (scene::ImGuiLayer *)layer;
        return;
    }
    layer_stack->push_layer(layer);
}

float Application::tick() {
    float to_sleep = glm::max(
        1.0f / fps - (util::Time::get_time<float>() - last_time),
        0.0f);
    util::Time::sleep(to_sleep);
    float current_time = util::Time::get_time<float>();
    float dt = (current_time - last_time); // get delta time
    last_time = current_time;
    return dt;
}

void Application::run() {
    while (running) {
        float dt = tick();
        auto input = events::InputManager::instance();
        input->prepare_for_update();
        events::Event event;
        while (input->poll_events(event)) {
            if (imgui_layer != nullptr) {
                imgui_layer->input(event);
            }
            switch ((events::EventType)event.type) {
            case events::EventType::quit:
                running = false;
                break;
            case events::EventType::window_event:
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
        util::Time::tick(dt);
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