#ifndef LIBGL2D_SCENE_LAYER_H
#define LIBGL2D_SCENE_LAYER_H

#include "libGL2D/core/using.h"

namespace libgl {

class Layer {
   public:
	Layer(const std::string &name = "Layer");
	virtual ~Layer();

	virtual void Render(float dt) = 0;
	virtual void Update(float dt) = 0;
	virtual void Input(float dt) = 0;

	const std::string &GetName() const { return name_; }

   protected:
	std::string name_;
};

}  // namespace libgl

#endif  // LIBGL2D_SCENE_LAYER_H