#ifndef OMEGA_SCENE_LAYERSTACK_H
#define OMEGA_SCENE_LAYERSTACK_H

#include <vector>

#include "omega/scene/layer.h"

namespace omega {

class LayerStack {
   public:
	LayerStack();
	~LayerStack();

	void Render(float dt);
	void Update(float dt);
	void Input(float dt);

	void PushLayer(Layer* layer);
	void PopLayer();

   private:
	std::vector<Layer*> layers_;
};

}  // namespace omega

#endif  // OMEGA_SCENE_LAYERSTACK_H