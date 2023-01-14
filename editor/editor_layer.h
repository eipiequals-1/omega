#ifndef EDITOR_EDITORLAYER_H
#define EDITOR_EDITORLAYER_H

#include "lib/imgui/imgui.h"

#include "omega/core/core.h"
#include "omega/events/events.h"
#include "omega/gfx/gfx.h"
#include "omega/scene/orthographic_camera.h"
#include "omega/scene/scene.h"
#include "omega/sound/sound.h"
#include "omega/util/util.h"

#include "editor/panels/resource_panel.h"
#include "editor/panels/scene_hierarchy.h"

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
