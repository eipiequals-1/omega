#ifndef OMEGA_SCENE_LAYER_HPP
#define OMEGA_SCENE_LAYER_HPP

#include <string>

namespace omega::scene {

class Layer {
  public:
    Layer(const std::string &name = "Layer", bool imgui = false) : name(name), imgui(imgui) {}
    virtual ~Layer() = default;

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

#endif // OMEGA_SCENE_LAYER_HPP
