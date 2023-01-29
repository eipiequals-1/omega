#include "app.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "omega/util/log.hpp"
#include "omega/util/math.hpp"
#include "omega/util/time.hpp"

namespace omega::core {

App *App::current_instance = nullptr;

App::App(const AppConfig &config) {
    current_instance = this;
    window = Window::instance();
    running = window->init(config.width, config.height, config.resizable, config.title);
    // init TTF_Font
    if (TTF_Init() != 0) {
        util::error("Unable to initialize SDL_ttf: '", SDL_GetError(), "'");
        running = false;
    }
    util::Time::init();
    last_time = util::Time::get_time<float>();
    globals = util::create_uptr<Globals>(Viewport(config.viewport_type, config.viewport_width, config.viewport_height), "Main Scene");
}

App::~App() {
    SDL_Quit();
    TTF_Quit();
}

float App::tick() {
    float to_sleep = glm::max(
        1.0f / fps - (util::Time::get_time<float>() - last_time),
        0.0f);
    util::Time::sleep(to_sleep);
    float current_time = util::Time::get_time<float>();
    float dt = (current_time - last_time); // get delta time
    last_time = current_time;
    return dt;
}

void App::run() {
    if (setup == nullptr) {
        running = false;
        util::error("App::setup not specified");
    } else {
        setup(globals.get());
    }
    while (running) {
        float dt = tick();
        
        auto &input = globals->input;
        input.prepare_for_update();
        
        events::Event event;
        while (input.poll_events(event)) {
            switch ((events::EventType)event.type) {
            case events::EventType::quit:
                running = false;
                break;
            case events::EventType::window_event:
                if (event.window.event == (uint32_t)events::WindowEvents::window_resized) {
                    // change window width, height data
                    Window::instance()->on_resize(event.window.data1, event.window.data2);
                    if (on_resize != nullptr) { on_resize(event.window.data1, event.window.data2, globals.get()); }
                }
                break;
            default:
                break;
            }
        }
        input.update();
        // perform the input
        if (this->input != nullptr) {
            if (this->input(dt, globals.get(), &input)) { break; }
        }
        if (this->update != nullptr) {
            if (this->update(dt, globals.get())) { break; }
        }
        if (this->render != nullptr) {
            this->render(dt, globals.get());
        }

        window->swap_buffers();
    }
}

} // namespace omega::core
