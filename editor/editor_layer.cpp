#include "editor_layer.h"

#include "omega/core/application.h"
#include "omega/gfx/errors.h"
#include "omega/gfx/shape_renderer.h"
#include "omega/gfx/sprite_batch.h"
#include "omega/vendor/imgui/imgui.h"

namespace editor {

EditorLayer::EditorLayer() : omega::Layer::Layer("Omega Editor Layer") {
	imgui_layer_ = omega::CreateUptr<omega::ImGuiLayer>(omega::Application::Instance().GetWindow().get());

	frame_buffer_ = omega::CreateUptr<omega::FrameBuffer>(1280, 720);
	camera_ = omega::CreateUptr<omega::OrthographicCamera>(0.0f, 1280.0f, 0.0f, 720.0f);
	scene_viewport_ = omega::CreateUptr<omega::Viewport>(omega::ViewportType::kFit, 1280, 720);
	scene_dock_size_.x = 1280.0f;
	scene_dock_size_.y = 720.0f;
}

EditorLayer::~EditorLayer() {
}

void EditorLayer::Input(float dt) {
	(void)dt;
	omega::Event event;
	omega::InputManager& input = omega::InputManager::Instance();
	while (input.PollEvents(event)) {
		imgui_layer_->Input(event);
		switch ((omega::EventType)event.type) {
		case omega::EventType::kQuit: {
			omega::Application::Instance().SetRunning(false);
			break;
		}
		case omega::EventType::kWindowEvent: {
			if (event.window.type == (uint32_t)omega::WindowEvents::kWindowResized) {
				omega::Application::Instance().OnResize(event.window.data1, event.window.data2);
			}
			break;
		}
		default:
			break;
		}
	}
	auto key_manager = input.GetKeyManager();
	if (key_manager->KeyPressed(omega::Key::kQ) && key_manager->KeyPressed(omega::Key::kLCtrl)) {
		omega::Application::Instance().SetRunning(false);
		return;
	}
}

void EditorLayer::Update(float dt) {
	(void)dt;
}

void EditorLayer::Render(float dt) {
	(void)dt;

	omega::Sptr<omega::Window> window = omega::Application::Instance().GetWindow();

	frame_buffer_->Bind();
	const auto fit_aspect_ratio = [](float src_width, float src_height, float max_width, float max_height) {
		const float ratio = glm::min(max_width / src_width, max_height / src_height);
		return glm::vec2(src_width * ratio, src_height * ratio);
	};

	const glm::vec2 size = fit_aspect_ratio(1280.0f, 720.0f, scene_dock_size_.x, scene_dock_size_.y);
	float margin_left = glm::round((scene_dock_size_.x - size.x) / 2.0f);
	float margin_bottom = glm::round((scene_dock_size_.y - size.y) / 2.0f);

	glViewport((GLint)margin_left, (GLint)margin_bottom, (uint32_t)glm::round(size.x), (uint32_t)glm::round(size.y));
	// omega::Log(scene_viewport_->GetViewportWidth(), scene_viewport_->GetViewportHeight(), scene_dock_size_.x, scene_dock_size_.y);
	// glViewport(0, 63, 1629, 916);
	// scene_viewport_->OnResize((uint32_t)glm::round(scene_dock_size_.x), (uint32_t)glm::round(scene_dock_size_.y));
	window->SetClearColor(glm::kBlack);
	window->Clear();
	// render scene to frame buffer
	omega::ShapeRenderer& renderer = omega::ShapeRenderer::Instance();
	camera_->RecalculateViewMatrix();
	renderer.SetViewProjectionMatrix(camera_->GetViewProjectionMatrix());

	renderer.Begin();
	renderer.Color(glm::kWhite);
	renderer.Rect(glm::rect(0.0f, 0.0f, scene_viewport_->GetViewportWidth(), scene_viewport_->GetViewportHeight()));

	renderer.Color(1.0f, 0.3f, 0.5f, 1.0f);
	renderer.Rect(glm::rect(scene_viewport_->GetViewportWidth() / 2.0f - 50.0f, scene_viewport_->GetViewportHeight() / 2.0f - 50.0f, 100.0f, 100.0f));

	renderer.End();
	frame_buffer_->Unbind();
	// reset viewport
	omega::Application::Instance().OnResize(window->GetWidth(), window->GetHeight());
	window->Clear();

	// render ImGui
	{
		imgui_layer_->Begin();

		static bool dockspace_open = true;
		static bool opt_fullscreen = true;
		// static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen) {
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspace_open, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Exit", "Ctrl+Q")) {
					omega::Application::Instance().SetRunning(false);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::End();
		ImGui::Begin("Settings");
		ImGui::Text("FPS: %.2f", 1 / dt);
		static glm::vec4 color;
		ImGui::ColorEdit4("Square Color", glm::value_ptr(color));
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0.0f, 0.0f});
		ImGui::Begin("Scene");

		ImVec2 viewport_panel_size = ImGui::GetContentRegionAvail();
		if (scene_dock_size_.x != viewport_panel_size.x || scene_dock_size_.y != viewport_panel_size.y) {
			frame_buffer_->Resize((uint32_t)viewport_panel_size.x, (uint32_t)viewport_panel_size.y);
		}
		scene_dock_size_ = {viewport_panel_size.x, viewport_panel_size.y};

		uint32_t texture_id = frame_buffer_->GetColorBuffer()->GetRendererID();
		ImGui::Image(reinterpret_cast<ImTextureID>(texture_id), viewport_panel_size, ImVec2{0.0f, 1.0f}, ImVec2{1.0f, 0.0f});
		ImGui::PopStyleVar();

		ImGui::End();

		imgui_layer_->End();
	}
	omega::SpriteBatch& batch = omega::SpriteBatch::Instance();
	batch.SetViewProjectionMatrix(camera_->GetViewProjectionMatrix());
	batch.BeginRender();

	// width / height = dest w / dest h
	float width = 100.0f;
	float height = width * frame_buffer_->GetColorBuffer()->GetHeight() / frame_buffer_->GetColorBuffer()->GetWidth();
	batch.RenderTexture(frame_buffer_->GetColorBuffer(), 400.0f, 200.0f, width, height);

	batch.EndRender();
}
}  // namespace editor