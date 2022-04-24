#ifndef _LIBGL2D_CORE_APPLICATION_H_
#define _LIBGL2D_CORE_APPLICATION_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "libGL2D/core/using.h"
#include "libGL2D/core/window.h"

namespace libgl {

class Application {
   public:
	Application(const WinBuilder& builder);
	virtual ~Application();

	virtual void Render(float dt);
	virtual void Update(float dt);
	virtual void Input(float dt);
	virtual float Tick();

	virtual void Run();

   protected:
	bool running_;
	Uptr<Window> window_;
	float fps_;
	uint32_t last_time_;
};
}  // namespace libgl

#endif  // _LIBGL2D_CORE_APPLICATION_H_