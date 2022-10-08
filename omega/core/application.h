#ifndef OMEGA_CORE_APPLICATION_H
#define OMEGA_CORE_APPLICATION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "omega/core/window.h"
#include "omega/events/events.h"
#include "omega/scene/scene.h"
#include "omega/util/util.h"

namespace omega::core {

using namespace omega::util;
using namespace omega::scene;
using namespace omega::events;

struct ApplicationConfig {
    u32 width = 800, height = 600;
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

    virtual void on_resize(u32 width, u32 height);

    static Application &instance() { return *current_instance; }

    sptr<Window> get_window() { return window; }

    void set_running(bool v) { running = v; }

  protected:
    void push_layer(Layer *layer);

    /**
     * Clamps the application by sleeping the CPU to run at Application::fps_
     * @return delta time in seconds from the last frame
     */
    virtual f32 tick();

    f32 fps;
    u32 last_time;
    sptr<Window> window;
    bool running;
    uptr<LayerStack> layer_stack;
    ImGuiLayer *imgui_layer;
    // singleton instance
    static Application *current_instance;
};
} // namespace omega::core

#endif // OMEGA_CORE_APPLICATION_H