#ifndef OMEGA_SCENE_IMGUILAYER_H
#define OMEGA_SCENE_IMGUILAYER_H

#include "omega/core/window.h"
#include "omega/events/event.h"
#include "omega/scene/layer.h"

namespace omega::scene {

using namespace omega::core;
using namespace omega::events;

class ImGuiLayer : public Layer {
  public:
    explicit ImGuiLayer(Window *window);
    virtual ~ImGuiLayer() override;

    virtual void set_dark_theme();

    void input(Event &event);
    virtual void input(f32 dt) override { (void)dt; }
    virtual void update(f32 dt) override { (void)dt; }
    virtual void render(f32 dt) override { (void)dt; }

    void begin();
    void end();

  private:
    Window *window;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_IMGUILAYER_H