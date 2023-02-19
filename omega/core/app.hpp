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
 * Configuration for the application including width, height, title, window settings, etc
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
 * Application class that handles everything from updating, rendering, handling input, etc
 *
 * @example
 *
 * omega::core::ApplicationConfig config;
 * // set application width, height, title, window settings etc
 * MyGame game(config);
 * // set the setup, update, render, input, on_resize functions
 * game.setup = [](Globals *globals) { // code }
 * game.run();
 */
class App final {
  public:
    std::function<void(Globals*)> setup = nullptr;
    std::function<bool(float, Globals*)> update = nullptr;
    std::function<void(float, Globals*)> render = nullptr;
    std::function<bool(float, Globals*, events::InputManager*)> input = nullptr;
    std::function<void(uint32_t, uint32_t, Globals*)> on_resize = nullptr;

    /**
     * Constructs an application given the configuration
     * @param config
     */
    explicit App(const AppConfig &config);
    ~App();

    /**
     * Abstraction of the application loop. Calls the Tick, Update, Input, and Render methods
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

  private:

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
