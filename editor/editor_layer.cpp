#include "editor_layer.h"

namespace editor {

EditorLayer::EditorLayer() : scene::ImGuiLayer::ImGuiLayer(omega::core::Application::instance().get_window().get()) {
    set_custom_styles();
    frame_buffer = util::create_uptr<gfx::FrameBuffer>(1280, 720);
    camera = util::create_uptr<scene::OrthographicCamera>(0.0f, 1280.0f, 0.0f, 720.0f);
    camera->recalculate_view_matrix();
    scene_viewport = util::create_uptr<core::Viewport>(core::ViewportType::k_fit, 1280, 720);

    // load music
    auto sound_manager = sound::SoundManager::instance();
    music = sound_manager->load_music("./editor/res/sound/DST-RailJet-LongSeamlessLoop.ogg");
    sound_manager->play_music(music, 1.0f);
}

EditorLayer::~EditorLayer() {
}

void EditorLayer::set_custom_styles() {
    set_dark_theme();
    ImGuiIO &io = ImGui::GetIO();
    io.FontDefault = io.Fonts->AddFontFromFileTTF("./editor/res/fnt/opensans/OpenSans-Regular.ttf", 18.0f);
}

void EditorLayer::input(f32 dt) {
    (void)dt;
    auto key_manager = events::InputManager::instance()->get_key_manager();
    if (key_manager->key_pressed(events::Key::k_q) && key_manager->key_pressed(events::Key::k_l_ctrl)) {
        core::Application::instance().set_running(false);
        return;
    }
}

void EditorLayer::update(f32 dt) {
    (void)dt;
}

void EditorLayer::render(f32 dt) {
    (void)dt;
    static glm::vec2 scene_dock_size(1280.0f, 720.0f);
    // util::log("frame buffer size", frame_buffer->get_width(), frame_buffer->get_height());

    util::sptr<core::Window> window = core::Application::instance().get_window();

    frame_buffer->bind();
    scene_viewport->on_resize(frame_buffer->get_width(), frame_buffer->get_height());

    window->set_clear_color(util::color::black);
    window->clear();
    // render scene to frame buffer
    gfx::ShapeRenderer &renderer = gfx::ShapeRenderer::instance();
    renderer.set_view_projection_matrix(camera->get_view_projection_matrix());

    renderer.begin();
    renderer.color(util::color::white);
    renderer.rect(glm::rectf(0.0f, 0.0f, camera->get_width(), camera->get_height()));

    renderer.color(1.0f, 0.3f, 0.5f, 1.0f);
    renderer.rect(glm::rectf(camera->get_width() / 2.0f - 50.0f, camera->get_height() / 2.0f - 50.0f, 100.0f, 100.0f));

    renderer.end();
    frame_buffer->unbind();
    // reset viewport
    window->clear();

    // render ImGui
    {
        begin();

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
                if (ImGui::MenuItem("New", "Ctrl+N")) {
                }
                if (ImGui::MenuItem("Open", "Ctrl+O")) {
                }
                if (ImGui::MenuItem("Exit", "Ctrl+Q")) {
                    core::Application::instance().set_running(false);
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::End();
        // scene hierarchy panel
        ImGui::Begin("Scene Hierarchy");
        ImGui::Text("FPS: %.2f", 1 / dt);
        static glm::vec4 color;
        ImGui::ColorEdit4("Square Color", glm::value_ptr(color));
        static float volume = 0.0f;

        ImGui::SliderFloat("Music Volume", &volume, 0.0f, 1.0f, nullptr, 1.0f);
        ImGui::End();
        // change sound volume
        sound::SoundManager::instance()->set_music_volume(music, volume);

        // Project panel
        ImGui::Begin("Project");

        ImGui::End();
        // Console panel
        ImGui::Begin("Console");
        ImGui::End();

        // scene viewport panel
        ImGui::Begin("Scene Viewport");

        ImVec2 viewport_panel_size = ImGui::GetContentRegionAvail();
        if (scene_dock_size.x != viewport_panel_size.x || scene_dock_size.y != viewport_panel_size.y) {
            frame_buffer->resize((u32)glm::round(viewport_panel_size.x), (u32)glm::round(viewport_panel_size.y));
            scene_dock_size = {viewport_panel_size.x, viewport_panel_size.y};
        }

        u32 texture_id = frame_buffer->get_color_buffer()->get_renderer_id();
        ImGui::Image(reinterpret_cast<ImTextureID>(texture_id), viewport_panel_size, ImVec2{0.0f, 1.0f}, ImVec2{1.0f, 0.0f});

        ImGui::End();

        // properties panel
        ImGui::Begin("Properties");
        ImGui::End();

        end();
    }
}
} // namespace editor