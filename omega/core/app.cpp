#include "app.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <fstream>

#include "imgui/imgui_impl_sdl.h"
#include "json/json.hpp"
#include "omega/core/engine_core.hpp"
#include "omega/math/math.hpp"
#include "omega/util/log.hpp"
#include "omega/util/time.hpp"
#include "tomlplusplus/toml.hpp"

namespace omega::core {

AppConfig AppConfig::from_config(const std::string &config_file) {
    if (config_file.ends_with("json")) {
        using json = nlohmann::json;
        std::ifstream f(config_file);
        json data = json::parse(f);

        AppConfig config;

        config.width =
            data.contains("width") ? (u32)data["width"] : config.width;
        config.height =
            data.contains("height") ? (u32)data["height"] : config.height;
        config.title =
            data.contains("title") ? (std::string)data["title"] : config.title;
        config.resizable = data.contains("resizable") ? (bool)data["resizable"]
                                                      : config.resizable;
        config.viewport_type = data.contains("viewport")
                                   ? data["viewport"] == "stretch"
                                         ? ViewportType::stretch
                                         : ViewportType::fit
                                   : ViewportType::fit;
        config.viewport_width = data.contains("viewport_width")
                                    ? (u32)data["viewport_width"]
                                    : config.viewport_width;
        config.viewport_height = data.contains("viewport_height")
                                     ? (u32)data["viewport_height"]
                                     : config.viewport_height;
        config.fps = data.contains("fps") ? (u32)data["fps"] : config.fps;
        config.imgui =
            data.contains("imgui") ? (bool)data["imgui"] : config.imgui;
        config.mouse_sensitivity = data.contains("mouse_sensitivity")
                                       ? (f32)data["mouse_sensitivity"]
                                       : config.mouse_sensitivity;
        return config;
    }
    // toml config file
    auto data = toml::parse_file(config_file);
    AppConfig config;

    config.title = data["default"]["title"].value_or(config.title);

    config.resizable = data["user"]["resizable"].value_or(config.resizable);
    config.fps = data["user"]["fps"].value_or(config.fps);
    config.mouse_sensitivity =
        data["user"]["sensitivity"].value_or(config.mouse_sensitivity);

    config.imgui = data["gfx"]["imgui"].value_or(config.imgui);
    config.width = data["gfx"]["width"].value_or(config.width);
    config.height = data["gfx"]["height"].value_or(config.height);
    config.viewport_type = data["gfx"]["viewport"].value_or("fit")
                               ? ViewportType::fit
                               : ViewportType::stretch;
    config.viewport_width =
        data["gfx"]["viewport_width"].value_or(config.viewport_width);
    config.viewport_height =
        data["gfx"]["viewport_height"].value_or(config.viewport_height);

    return config;
}

App *App::current_instance = nullptr;

App::App(const AppConfig &config) {
    current_instance = this;
    window = Window::instance();
    running = window->init(
        config.width, config.height, config.resizable, config.title);

    init();
    last_time = util::time::get_time<f32>();
    fps = config.fps;
    globals = util::create_uptr<Globals>(Viewport(config.viewport_type,
                                                  config.viewport_width,
                                                  config.viewport_height),
                                         "Main Scene");
    globals->input.mouse.set_sensitivity(config.mouse_sensitivity);

    // init imgui
    imgui = config.imgui;
    setup_imgui(window);
    if (imgui) {
        util::info("Dear Imgui successfully initialized.");
    }
}

App::~App() {
    quit(imgui);
}

f32 App::tick() {
    f32 to_sleep =
        math::max(1.0f / fps - (util::time::get_time<f32>() - last_time), 0.0f);
    util::time::sleep(to_sleep);
    f32 current_time = util::time::get_time<f32>();
    f32 dt = (current_time - last_time); // get delta time
    last_time = current_time;
    return dt;
}

void App::frame() {
    f32 dt = tick();

    auto &input = globals->input;
    input.prepare_for_update();

    events::Event event;
    while (input.poll_events(event)) {
        if (imgui) {
            ImGui_ImplSDL2_ProcessEvent(&event);
        }
        switch ((events::EventType)event.type) {
            case events::EventType::quit:
                running = false;
                break;
            case events::EventType::window_event:
                if (event.window.event ==
                    (u32)events::WindowEvents::window_resized) {
                    // change window width, height data
                    Window::instance()->on_resize(event.window.data1,
                                                  event.window.data2);
                    on_resize(event.window.data1, event.window.data2);
                }
                break;
            case events::EventType::mouse_wheel:
                input.mouse.scroll_wheel =
                    math::vec2((f32)event.wheel.x, (f32)event.wheel.y);
            default:
                break;
        }
    }
    input.update();
    // perform the input, update, and render
    this->input(dt);
    this->update(dt);

    begin_imgui_frame();
    this->render(dt);
    end_imgui_frame(window);

    window->swap_buffers();
}

static void update_loop() {
    auto &app = App::instance();
    app.frame();
}

void App::run() {
    setup();

#ifdef EMSCRIPTEN
    emscripten_set_main_loop(update_loop, 0, 1);
#else
    while (running) {
        update_loop();
    }
#endif
}

} // namespace omega::core
