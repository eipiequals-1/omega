#ifndef OMEGA_SCENE_IMGUILAYER_H
#define OMEGA_SCENE_IMGUILAYER_H

#include "omega/core/window.h"
#include "omega/events/event.h"
#include "omega/scene/layer.h"

namespace omega {

class ImGuiLayer : public Layer {
   public:
	explicit ImGuiLayer(Window* window);
	virtual ~ImGuiLayer() override;

	void Input(Event& event);
	virtual void Input(float dt) override { (void)dt; }
	virtual void Update(float dt) override { (void)dt; }
	virtual void Render(float dt) override { (void)dt; }

	void Begin();
	void End();

   private:
	Window* window_;
};

}  // namespace omega

#endif  // OMEGA_SCENE_IMGUILAYER_H