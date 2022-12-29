#ifndef OMEGA_CORE_APPLICATION_H
#define OMEGA_CORE_APPLICATION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "omega/core/window.h"
#include "omega/events/events.h"
#include "omega/scene/imgui_layer.h"
#include "omega/scene/layer.h"
#include "omega/scene/layer_stack.h"
#include "omega/util/std.h"

namespace omega::core {

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

    util::sptr<Window> get_window() { return window; }

    void set_running(bool v) { running = v; }

  protected:
    void push_layer(scene::Layer *layer);

    /**
     * Clamps the application by sleeping the CPU to run at Application::fps
     * @return delta time in seconds from the last frame
     */
    virtual float tick();

    float fps = 60.0f;
    float last_time = 0.0f;
    util::sptr<Window> window = nullptr;
    bool running = true;
    util::uptr<scene::LayerStack> layer_stack = nullptr;
    scene::ImGuiLayer *imgui_layer = nullptr;
    // singleton instance
    static Application *current_instance;
};
} // namespace omega::core

#endif // OMEGA_CORE_APPLICATION_H