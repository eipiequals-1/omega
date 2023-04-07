#ifndef OMEGA_LEVELEDITOR_SCENE_HPP
#define OMEGA_LEVELEDITOR_SCENE_HPP

#include "omega/gfx/gfx.hpp"
#include "omega/scene/orthographic_camera.hpp"
#include "omega/util/util.hpp"

class Scene {
  public:
    Scene();
    void render();

  private:
    omega::util::uptr<omega::gfx::FrameBuffer> framebuffer;
    omega::scene::OrthographicCamera camera;
};

#endif // OMEGA_LEVELEDITOR_SCENE_HPP
