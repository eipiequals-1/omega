#ifndef OMEGA_SCENE_IMGUILAYER_HPP
#define OMEGA_SCENE_IMGUILAYER_HPP

#include "omega/core/window.hpp"
#include "omega/events/event.hpp"
#include "omega/scene/layer.hpp"

namespace omega::scene {

using namespace omega::core;
using namespace omega::events;

class ImGuiLayer : public Layer {
  public:
    explicit ImGuiLayer(Window *window);
    virtual ~ImGuiLayer() override;

    virtual void set_dark_theme();

    void input(Event &event);
    virtual void input(float dt) override {
        (void)dt;
    }
    virtual void update(float dt) override {
        (void)dt;
    }
    virtual void render(float dt) override {
        (void)dt;
    }

    void begin();
    void end();

  private:
    Window *window = nullptr;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_IMGUILAYER_HPP
