#ifndef OMEGA_SCENE_LAYER_H
#define OMEGA_SCENE_LAYER_H

#include "omega/util/util.h"

namespace omega::scene {

class Layer {
  public:
    Layer(const std::string &name = "Layer", bool imgui = false);
    virtual ~Layer();

    virtual void render(f32 dt) = 0;
    virtual void update(f32 dt) = 0;
    virtual void input(f32 dt) = 0;

    const std::string &get_name() const { return name; }
    bool is_imgui() const { return imgui; }

  protected:
    std::string name;
    bool imgui;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_LAYER_H