#ifndef OMEGA_CORE_APPLICATION_H
#define OMEGA_CORE_APPLICATION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "omega/core/using.h"
#include "omega/core/window.h"
#include "omega/scene/layer.h"
#include "omega/scene/layer_stack.h"

namespace omega {

struct ApplicationConfig {
	uint32_t width = 800, height = 600;
	std::string title = "Application";
	bool resizable = true;
};

/**
 * Application class that handles everything from updating, rendering, handling input, etc
 *
 * Intended Use:
 *
 * class MyGame : public Application { . . . }
 *
 * omega::ApplicationConfig config;
 * // set application width, height, title, window settings etc
 * MyGame game;
 * game.Run();
 */
class Application {
   public:
	explicit Application(const ApplicationConfig& config);
	virtual ~Application();

	/**
	 * Abstraction of the application loop. Calls the Tick, Update, Input, and Render methods
	 */
	virtual void Run();

	virtual void OnResize(uint32_t width, uint32_t height);

	static Application& Instance() { return *instance_; }

	Sptr<Window> GetWindow() { return window_; }

	void SetRunning(bool v) { running_ = v; }

   protected:
	void PushLayer(Layer* layer);

	/**
	 * Clamps the application by sleeping the CPU to run at Application::fps_
	 * @return delta time in seconds from the last frame
	 */
	virtual float Tick();

	float fps_;
	uint32_t last_time_;
	Sptr<Window> window_;
	bool running_;
	Uptr<LayerStack> layer_stack_;
	// singleton instance
	static Application* instance_;
};
}  // namespace omega

#endif  // OMEGA_CORE_APPLICATION_H