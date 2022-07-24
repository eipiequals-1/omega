#ifndef EDITOR_EDITORLAYER_H
#define EDITOR_EDITORLAYER_H

#include "omega/core/orthographic_camera.h"
#include "omega/core/using.h"
#include "omega/core/viewport.h"
#include "omega/events/event.h"
#include "omega/events/input_manager.h"
#include "omega/gfx/frame_buffer.h"
#include "omega/scene/imgui_layer.h"
#include "omega/scene/layer.h"

namespace editor {

class EditorLayer : public omega::Layer {
   public:
	EditorLayer();
	~EditorLayer() override;

	void Render(float dt) override;
	void Update(float dt) override;
	void Input(float dt) override;

   private:
	omega::Uptr<omega::ImGuiLayer> imgui_layer_;
	omega::Uptr<omega::FrameBuffer> frame_buffer_;
	omega::Uptr<omega::OrthographicCamera> camera_;
	omega::Uptr<omega::Viewport> scene_viewport_;
	glm::vec2 scene_dock_size_;
};

}  // namespace editor

#endif  // EDITOR_EDITORLAYER_H