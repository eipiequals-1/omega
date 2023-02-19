#include "app.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "omega/util/log.hpp"
#include "omega/util/math.hpp"
#include "omega/util/time.hpp"
#include "lib/imgui/imgui.h"
#include "lib/imgui/imgui_impl_sdl.h"
#include "lib/imgui/imgui_impl_opengl3.h"

static void setup_imgui(omega::core::Window *window) {
    // setup imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    /* ImGui::StyleColorsDark(); */

    ImGui_ImplSDL2_InitForOpenGL(window->get_native_window(), window->get_gl_context());
    const char version[] = "#version 450";
    ImGui_ImplOpenGL3_Init(version);
}

static void quit_imgui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

static void begin_imgui_frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

static void end_imgui_frame(omega::core::Window *window) {
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)window->get_width(), (float)window->get_height());

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

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
    fps = config.fps;
    globals = util::create_uptr<Globals>(Viewport(config.viewport_type, config.viewport_width, config.viewport_height), "Main Scene");

    // init imgui
    imgui = config.imgui;
    setup_imgui(window);
}

App::~App() {
    quit_imgui();
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
            if (imgui) {
                ImGui_ImplSDL2_ProcessEvent(&event);
            }
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
            case events::EventType::mouse_wheel:
                input.scroll_wheel = glm::vec2((float)event.wheel.x, (float)event.wheel.y);
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
        begin_imgui_frame();
        if (this->render != nullptr) {
            this->render(dt, globals.get());
        }
        end_imgui_frame(window);

        window->swap_buffers();
    }
}

} // namespace omega::core
