#ifndef OMEGA_CORE_APPLICATION_H
#define OMEGA_CORE_APPLICATION_H

#include "omega/core/window.h"
#include "omega/events/events.h"
#include "omega/scene/imgui_layer.h"
#include "omega/scene/layer.h"
#include "omega/scene/layer_stack.h"
#include "omega/util/std.h"

namespace omega::core {

/**
 * Configuration for the application including width, height, title, window settings, etc
 */
struct ApplicationConfig {
    uint32_t width = 800, height = 600;
    std::string title = "Application";
    bool resizable = true;
};

/**
 * Application class that handles everything from updating, rendering, handling input, etc
 *
 * @example
 * class MyGame : public omega::core::Application { . . . }
 *
 * omega::core::ApplicationConfig config;
 * // set application width, height, title, window settings etc
 * MyGame game(config);
 * game.run();
 */
class Application {
  public:
    /**
     * Constructs an application given the configuration
     * @param config
     */
    explicit Application(const ApplicationConfig &config);
    virtual ~Application();

    /**
     * Abstraction of the application loop. Calls the Tick, Update, Input, and Render methods
     */
    virtual void run();

    /**
     * Called when the application window is resized
     * @param width
     * @param height
     */
    virtual void on_resize(uint32_t width, uint32_t height);

    /**
     * @return the current application
     */
    static Application &instance() { return *current_instance; }

    /**
     * @return the window
     */
    util::sptr<Window> get_window() { return window; }

    /**
     * Useful to quit the application from any class
     * @param v set the application run state
     */
    void set_running(bool v) { running = v; }

  protected:
    /**
     * Push a layer to the top of the layer stack, i.e. it will be the top most layer
     * @param layer dynamically allocated
     */
    void push_layer(scene::Layer *layer);

    /**
     * Clamps the application by sleeping the CPU to run at Application::fps
     * @return delta time in seconds from the last frame
     */
    float tick();

    // application state
    bool running = true;
    util::sptr<Window> window = nullptr;

    // clock and timing
    float fps = 60.0f;
    float last_time = 0.0f;

    // different layers
    util::uptr<scene::LayerStack> layer_stack = nullptr;
    scene::ImGuiLayer *imgui_layer = nullptr;

    // singleton instance
    static Application *current_instance;
};
} // namespace omega::core

#endif // OMEGA_CORE_APPLICATION_H