#ifndef EDITOR_EDITORLAYER_H
#define EDITOR_EDITORLAYER_H

#include "omega/core/core.h"
#include "omega/events/events.h"
#include "omega/gfx/gfx.h"
#include "omega/scene/scene.h"
#include "omega/sound/sound.h"
#include "omega/util/util.h"
#include "omega/vendor/imgui/imgui.h"

namespace editor {

using namespace omega;

class EditorLayer : public scene::ImGuiLayer {
  public:
    EditorLayer();
    ~EditorLayer() override;

    void render(float dt) override;
    void update(float dt) override;
    void input(float dt) override;

  private:
    util::uptr<gfx::FrameBuffer> frame_buffer;
    util::uptr<scene::OrthographicCamera> camera;
    util::uptr<core::Viewport> scene_viewport;
    sound::MusicID music;
};

} // namespace editor

#endif // EDITOR_EDITORLAYER_H