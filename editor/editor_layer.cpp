#include "editor_layer.h"

namespace editor {

EditorLayer::EditorLayer() : scene::Layer::Layer("Omega Editor Layer") {
    imgui_layer = util::create_uptr<scene::ImGuiLayer>(core::Application::instance().get_window().get());
    imgui_layer->set_dark_theme();

    frame_buffer = util::create_uptr<gfx::FrameBuffer>(1280, 720);
    camera = util::create_uptr<core::OrthographicCamera>(0.0f, 1280.0f, 0.0f, 720.0f);
    scene_viewport = util::create_uptr<core::Viewport>(core::ViewportType::k_fit, 1280, 720);
    scene_dock_size.x = 1280.0f;
    scene_dock_size.y = 720.0f;
}

EditorLayer::~EditorLayer() {
}

void EditorLayer::input(float dt) {
    (void)dt;
    events::Event event;
    util::sptr<events::InputManager> input = events::InputManager::instance();
    input->prepare_for_update();
    while (input->poll_events(event)) {
        imgui_layer->input(event);
        switch ((events::EventType)event.type) {
        case events::EventType::k_quit: {
            core::Application::instance().set_running(false);
            break;
        }
        case events::EventType::k_window_event: {
            if (event.window.type == (uint32_t)events::WindowEvents::k_window_resized) {
                core::Application::instance().on_resize(event.window.data1, event.window.data2);
            }
            break;
        }
        default:
            break;
        }
    }
    input->update();
    auto key_manager = input->get_key_manager();
    if (key_manager->key_pressed(events::Key::k_q) && key_manager->key_pressed(events::Key::k_l_ctrl)) {
        core::Application::instance().set_running(false);
        return;
    }
}

void EditorLayer::update(float dt) {
    (void)dt;
}

void EditorLayer::render(float dt) {
    (void)dt;

    util::sptr<core::Window> window = core::Application::instance().get_window();

    frame_buffer->bind();
    // const auto fit_aspect_ratio = [](float src_width, float src_height, float max_width, float max_height) {
    // 	const float ratio = glm::min(max_width / src_width, max_height / src_height);
    // 	return glm::vec2(src_width * ratio, src_height * ratio);
    // };

    // const glm::vec2 size = fit_aspect_ratio(1280.0f, 720.0f, scene_dock_size_.x, scene_dock_size_.y);
    // float margin_left = glm::round((scene_dock_size_.x - size.x) / 2.0f);
    // float margin_bottom = glm::round((scene_dock_size_.y - size.y) / 2.0f);

    // glViewport((GLint)margin_left, (GLint)margin_bottom, (uint32_t)glm::round(size.x), (uint32_t)glm::round(size.y));
    // omega::Log(scene_viewport_->GetViewportWidth(), scene_viewport_->GetViewportHeight(), scene_dock_size_.x, scene_dock_size_.y);

    scene_viewport->on_resize((uint32_t)glm::round(scene_dock_size.x), (uint32_t)glm::round(scene_dock_size.y));
    // glViewport(0, 63, 1629, 916);
    glViewport(0, 0, frame_buffer->get_width(), frame_buffer->get_height());
    // omega::Log("viewport_size:", scene_viewport_->GetViewportWidth());
    window->set_clear_color(util::color::black);
    window->clear();
    // render scene to frame buffer
    gfx::ShapeRenderer &renderer = gfx::ShapeRenderer::instance();
    camera->recalculate_view_matrix();
    renderer.set_view_projection_matrix(camera->get_view_projection_matrix());

    renderer.begin();
    renderer.color(util::color::white);
    renderer.rect(glm::rectf(0.0f, 0.0f, frame_buffer->get_width(), frame_buffer->get_height()));

    renderer.color(1.0f, 0.3f, 0.5f, 1.0f);
    renderer.rect(glm::rectf(scene_viewport->get_viewport_width() / 2.0f - 50.0f, scene_viewport->get_viewport_height() / 2.0f - 50.0f, 100.0f, 100.0f));

    renderer.end();
    frame_buffer->unbind();
    // reset viewport
    core::Application::instance().on_resize(window->get_width(), window->get_height());
    window->clear();

    // render ImGui
    {
        imgui_layer->begin();

        static bool dockspace_open = true;
        static bool opt_fullscreen = true;
        // static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            const ImGuiViewport *viewport = ImGui::GetMainViewport();
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
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit", "Ctrl+Q")) {
                    core::Application::instance().set_running(false);
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
        if (scene_dock_size.x != viewport_panel_size.x || scene_dock_size.y != viewport_panel_size.y) {
            frame_buffer->resize((uint32_t)glm::round(viewport_panel_size.x), (uint32_t)glm::round(viewport_panel_size.y));
            // omega::Log("Width available:", viewport_panel_size.x);
        }
        scene_dock_size = {viewport_panel_size.x, viewport_panel_size.y};

        uint32_t texture_id = frame_buffer->get_color_buffer()->get_renderer_id();
        ImGui::Image(reinterpret_cast<ImTextureID>(texture_id), viewport_panel_size, ImVec2{0.0f, 1.0f}, ImVec2{1.0f, 0.0f});
        ImGui::PopStyleVar();

        ImGui::End();

        imgui_layer->end();
    }
    gfx::SpriteBatch &batch = gfx::SpriteBatch::instance();
    batch.set_view_projection_matrix(camera->get_view_projection_matrix());
    batch.begin_render();

    // width / height = dest w / dest h
    float width = 100.0f;
    float height = width * frame_buffer->get_height() / frame_buffer->get_width();
    batch.render_texture(frame_buffer->get_color_buffer().get(), 400.0f, 200.0f, width, height);

    batch.end_render();
    // omega::GLCheckError();
}
} // namespace editor