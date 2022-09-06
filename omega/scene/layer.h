#ifndef OMEGA_SCENE_LAYER_H
#define OMEGA_SCENE_LAYER_H

#include "omega/util/util.h"

namespace omega::scene {

class Layer {
  public:
    Layer(const std::string &name = "Layer");
    virtual ~Layer();

    virtual void render(f32 dt) = 0;
    virtual void update(f32 dt) = 0;
    virtual void input(f32 dt) = 0;

    const std::string &get_name() const { return name; }

  protected:
    std::string name;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_LAYER_H