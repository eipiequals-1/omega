#ifndef OMEGA_CORE_APPLICATION_HPP
#define OMEGA_CORE_APPLICATION_HPP

#include <functional>

#include "omega/core/globals.hpp"
#include "omega/core/window.hpp"
#include "omega/core/viewport.hpp"
#include "omega/events/events.hpp"
#include "omega/util/std.hpp"

namespace omega::core {

/**
 * Configuration for the application including width, height, title, window
 * settings, etc
 */
struct AppConfig {
    uint32_t width = 900, height = 450;
    std::string title = "Omega App";
    bool resizable = true;
    // viewport settings
    ViewportType viewport_type = ViewportType::stretch;
    uint32_t viewport_width = 900, viewport_height = 450;
    // fps
    uint32_t fps = 60;
    // imgui
    bool imgui = false;
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
    virtual void update(float dt) {(void)dt;};
    virtual void input(float dt) { (void)dt;}
    virtual void render(float dt) { (void)dt; }
    virtual void on_resize(uint32_t width, uint32_t height) {
        globals->scene.on_resize(width, height);
    }

    void frame();

  protected:

    /**
     * Clamps the application by sleeping the CPU to run at Application::fps
     * @return delta time in seconds from the last frame
     */
    float tick();

    // application state
    bool running = true;
    Window* window = nullptr;
    util::uptr<Globals> globals = nullptr;
    bool imgui = false;

    // clock and timing
    float fps = 60.0f;
    float last_time = 0.0f;

    // singleton instance
    static App *current_instance;
};
} // namespace omega::core

#endif // OMEGA_CORE_APPLICATION_HPP
