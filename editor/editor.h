#ifndef EDITOR_EDITOR_H
#define EDITOR_EDITOR_H

#include "omega/core/application.h"
#include "omega/core/orthographic_camera.h"
#include "omega/core/using.h"
#include "omega/core/viewport.h"
#include "omega/events/event.h"
#include "omega/events/input_manager.h"
#include "omega/gfx/frame_buffer.h"
#include "omega/scene/imgui_layer.h"

namespace editor {

class EditorApplication : public omega::Application {
   public:
	EditorApplication(const omega::ApplicationConfig &config);

	void Input(float dt) override;
	void Update(float dt) override;
	void Render(float dt) override;

   private:
	omega::Uptr<omega::ImGuiLayer> imgui_layer_;
	omega::Uptr<omega::FrameBuffer> frame_buffer_;
	omega::Uptr<omega::OrthographicCamera> camera_;
	omega::Uptr<omega::Viewport> scene_viewport_;
	glm::vec2 scene_dock_size_;
};
}  // namespace editor

#endif  // EDITOR_EDITOR_H