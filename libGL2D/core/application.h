#ifndef _LIBGL2D_CORE_APPLICATION_H_
#define _LIBGL2D_CORE_APPLICATION_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "libGL2D/core/using.h"
#include "libGL2D/core/window.h"

namespace libgl {

/**
 * Application class that handles everything from updating, rendering, handling input, etc
 *
 * Intended Use:
 *
 * class MyGame : public libgl::Application { . . . }
 *
 * MyGame game;
 *
 * game.Run();
 */
class Application {
   public:
	Application(const WinBuilder& builder);
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
	 * Abstraction of the application. Calls the Tick, Update, Input, and Render methods
	 */
	virtual void Run();

   protected:
	bool running_;
	Uptr<Window> window_;
	float fps_;
	uint32_t last_time_;
};
}  // namespace libgl

#endif  // _LIBGL2D_CORE_APPLICATION_H_