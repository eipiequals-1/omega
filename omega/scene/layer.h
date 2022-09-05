#ifndef OMEGA_SCENE_LAYER_H
#define OMEGA_SCENE_LAYER_H

#include "omega/util/util.h"

namespace omega {

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

}  // namespace omega

#endif  // OMEGA_SCENE_LAYER_H