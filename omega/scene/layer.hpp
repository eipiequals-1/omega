#ifndef OMEGA_SCENE_LAYER_HPP
#define OMEGA_SCENE_LAYER_HPP

#include <string>

#include "omega/util/types.hpp"

namespace omega::scene {

class Layer {
  public:
    Layer(const std::string &name = "Layer", bool imgui = false)
        : name(name), imgui(imgui) {}
    virtual ~Layer() = default;

    virtual void render(f32 dt) = 0;
    virtual void update(f32 dt) = 0;
    virtual void input(f32 dt) = 0;

    const std::string &get_name() const {
        return name;
    }
    bool is_imgui() const {
        return imgui;
    }

  protected:
    std::string name;
    bool imgui;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_LAYER_HPP
