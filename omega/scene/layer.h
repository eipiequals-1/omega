#ifndef OMEGA_SCENE_LAYER_H
#define OMEGA_SCENE_LAYER_H

#include "omega/util/util.h"

namespace omega::scene {

class Layer {
  public:
    Layer(const std::string &name = "Layer", bool imgui = false);
    virtual ~Layer();

    virtual void render(float dt) = 0;
    virtual void update(float dt) = 0;
    virtual void input(float dt) = 0;

    const std::string &get_name() const { return name; }
    bool is_imgui() const { return imgui; }

  protected:
    std::string name;
    bool imgui;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_LAYER_H