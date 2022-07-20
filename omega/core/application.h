#ifndef OMEGA_CORE_APPLICATION_H
#define OMEGA_CORE_APPLICATION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "omega/core/using.h"
#include "omega/core/window.h"
#include "omega/events/event.h"
#include "omega/events/input_manager.h"

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
	 * Draws every entity on the screen using any renderer
	 * @param dt delta time if needed
	 */
	virtual void Render(float dt);

	/**
	 * Updates every entity based on the delta time
	 * @param dt delta time for frame independent updating
	 */
	virtual void Update(float dt);

	/**
	 * Handles user input such as mouse, keyboard, and window events
	 * @param dt delta time if necessary
	 */
	virtual void Input(float dt);

	/**
	 * Clamps the application by sleeping the CPU to run at Application::fps_
	 * @return delta time in seconds from the last frame
	 */
	virtual float Tick();

	/**
	 * Abstraction of the application loop. Calls the Tick, Update, Input, and Render methods
	 */
	virtual void Run();

	virtual void OnResize(uint32_t width, uint32_t height);

   protected:
	float fps_;
	uint32_t last_time_;
	Uptr<Window> window_;
	bool running_;
};
}  // namespace omega

#endif  // OMEGA_CORE_APPLICATION_H