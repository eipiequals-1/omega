#ifndef OMEGA_CORE_APPLICATION_HPP
#define OMEGA_CORE_APPLICATION_HPP

#include <functional>

#include "omega/core/globals.hpp"
#include "omega/core/window.hpp"
#include "omega/core/viewport.hpp"
#include "omega/events/events.hpp"
#include "omega/math/math.hpp"
#include "omega/util/std.hpp"
#include "omega/util/types.hpp"

namespace omega::core {

/**
 * Configuration for the application including width, height, title, window
 * settings, etc
 */
struct AppConfig {
    u32 width = 900, height = 450;
    std::string title = "Omega App";
    bool resizable = true;
    // viewport settings
    ViewportType viewport_type = ViewportType::stretch;
    u32 viewport_width = 900, viewport_height = 450;
    // fps
    u32 fps = 60;
    // imgui
    bool imgui = false;
    
    f32 mouse_sensitivity = 0.1f;

    static AppConfig from_config(const std::string &config_file);
};

/**
 * Application class that handles everything from updating, rendering, handling
 * input, etc
 *
 * @example
 *
 * class MyGame : public App {}
 *
 * int main() {
 *
 * omega::core::AppConfig config;
 *
 * // set application width, height, title, window settings etc
 *
 * MyGame game(config);
 *
 * game.run();
 * }
 */
class App {
  public:
    /**
     * Constructs an application given the configuration
     * @param config
     */
    explicit App(const AppConfig &config);
    ~App();

    /**
     * Abstraction of the application loop. Calls the tick, update, input, and 
     * render methods
     */
    void run();

     /**
     * @return the current application
     */
    static App &instance() { return *current_instance; }

    /**
     * @return the window
     */
    Window* get_window() { return window; }

    virtual void setup() {};
    virtual void update(f32 dt) {(void)dt;};
    virtual void input(f32 dt) { (void)dt;}
    virtual void render(f32 dt) { (void)dt; }
    virtual void on_resize(u32 width, u32 height) {
        globals->scene.on_resize(width, height);
    }

    void frame();

  protected:

    /**
     * Clamps the application by sleeping the CPU to run at Application::fps
     * @return delta time in seconds from the last frame
     */
    f32 tick();

    // application state
    bool running = true;
    Window* window = nullptr;
    util::uptr<Globals> globals = nullptr;
    bool imgui = false;

    // clock and timing
    f32 fps = 60.0f;
    f32 last_time = 0.0f;

    // singleton instance
    static App *current_instance;
};
} // namespace omega::core

#endif // OMEGA_CORE_APPLICATION_HPP
