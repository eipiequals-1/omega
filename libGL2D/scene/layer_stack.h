#ifndef LIBGL2D_SCENE_LAYERSTACK_H
#define LIBGL2D_SCENE_LAYERSTACK_H

#include <vector>

#include "libGL2D/scene/layer.h"

namespace libgl {

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

}  // namespace libgl

#endif  // LIBGL2D_SCENE_LAYERSTACK_H