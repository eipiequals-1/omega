#ifndef EDITOR_EDITORLAYER_H
#define EDITOR_EDITORLAYER_H

#include "lib/imgui/imgui.h"

#include "omega/core/core.hpp"
#include "omega/events/events.hpp"
#include "omega/gfx/gfx.hpp"
#include "omega/scene/orthographic_camera.hpp"
#include "omega/scene/scene.hpp"
#include "omega/sound/sound.hpp"
#include "omega/util/util.hpp"

#include "editor/panels/resource_panel.hpp"
#include "editor/panels/scene_hierarchy.hpp"

namespace omega {

class EditorLayer : public scene::ImGuiLayer {
  public:
    EditorLayer();
    ~EditorLayer() override;

    void render(float dt) override;
    void update(float dt) override;
    void input(float dt) override;

  private:
    void set_custom_styles();
    // render methods
    void dockspace();
    void render_to_framebuffer(float dt);

    util::uptr<gfx::FrameBuffer> frame_buffer;
    util::uptr<scene::OrthographicCamera> camera;
    util::uptr<core::Viewport> scene_viewport;

    // panels
    util::uptr<SceneHierarchy> scene_hierarchy;
    util::uptr<ResourcePanel> project_panel;

    // scene
    util::sptr<scene::Scene> scene;
};

} // namespace omega

#endif // EDITOR_EDITORLAYER_H
