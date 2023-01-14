#include "editor_layer.h"

#include "omega/scene/components.h"

namespace omega {

EditorLayer::EditorLayer() : scene::ImGuiLayer::ImGuiLayer(omega::core::Application::instance().get_window().get()) {
    set_custom_styles();
    gfx::enable_blending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    frame_buffer = util::create_uptr<gfx::FrameBuffer>(1280, 720);
    camera = util::create_uptr<scene::OrthographicCamera>(0.0f, 1280.0f, 0.0f, 720.0f);
    camera->recalculate_view_matrix();
    scene_viewport = util::create_uptr<core::Viewport>(core::ViewportType::fit, 1280, 720);

    scene = util::create_sptr<scene::Scene>("Main Scene");
    // add camera
    scene::Entity camera = scene->create_entity("Main Camera");
    auto &cam_component = camera.add_component<scene::CameraComponent>(scene::CameraComponent::ProjectionType::orthographic);
    cam_component.ortho.set_projection(0.0f, 1280.0f, 0.0f, 720.0f);
    cam_component.ortho.recalculate_view_matrix();

    // add square
    scene::Entity square = scene->create_entity("Sprite");
    auto &transform = square.add_component<scene::TransformComponent>();
    transform.position = glm::vec3(100.0f, 100.0f, 0.0f);
    transform.scale = glm::vec3(500.0f);

    auto &sprite = square.add_component<scene::SpriteComponent>();
    sprite.color = util::color::white;
    sprite.texture = gfx::texture::Texture::create_from_file("./editor/res/ui/file_icon.png");

    // create panels
    scene_hierarchy = util::create_uptr<SceneHierarchy>(scene);
    project_panel = util::create_uptr<ResourcePanel>();
}

EditorLayer::~EditorLayer() {
}

void EditorLayer::input(float dt) {
    (void)dt;
    auto key_manager = events::InputManager::instance()->get_key_manager();
    if (
        (key_manager->key_pressed(events::Key::k_q) && key_manager->key_pressed(events::Key::k_l_ctrl)) ||
        key_manager->key_pressed(events::Key::k_escape)) {
        core::Application::instance().set_running(false);
        return;
    }
}

void EditorLayer::update(float dt) {
    (void)dt;
    scene->update(dt);
}

void EditorLayer::render(float dt) {
    static glm::vec2 scene_dock_size(1280.0f, 720.0f);
    render_to_framebuffer(dt);

    auto window = core::Application::instance().get_window();
    // reset viewport
    gfx::viewport(0, 0, window->get_width(), window->get_height());
    window->clear();

    // render ImGui
    {
        begin();

        dockspace();
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
        // render panels

        scene_hierarchy->render();
        project_panel->render();

        // Console panel
        ImGui::Begin("Console");
        ImGui::End();

        // scene viewport panel
        ImGui::Begin("Scene Viewport");

        ImVec2 viewport_panel_size = ImGui::GetContentRegionAvail();
        if (scene_dock_size.x != viewport_panel_size.x || scene_dock_size.y != viewport_panel_size.y) {
            frame_buffer->resize((uint32_t)glm::round(viewport_panel_size.x), (uint32_t)glm::round(viewport_panel_size.y));
            scene_dock_size = {viewport_panel_size.x, viewport_panel_size.y};
        }

        uint32_t texture_id = frame_buffer->get_color_buffer()->get_renderer_id();
        ImGui::Image(reinterpret_cast<ImTextureID>(texture_id), viewport_panel_size, ImVec2{0.0f, 1.0f}, ImVec2{1.0f, 0.0f});

        ImGui::End();

        end();
    }
}

void EditorLayer::set_custom_styles() {
    set_dark_theme();
    ImGuiIO &io = ImGui::GetIO();
    io.FontDefault = io.Fonts->AddFontFromFileTTF("./editor/res/fnt/opensans/OpenSans-Regular.ttf", 18.0f);
}

void EditorLayer::dockspace() {
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

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

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
}

void EditorLayer::render_to_framebuffer(float dt) {
    (void)dt;
    frame_buffer->bind();

    // set viewport
    scene_viewport->on_resize(frame_buffer->get_width(), frame_buffer->get_height());

    // render scene to frame buffer
    scene->render(dt);
    // unbind
    gfx::FrameBuffer::unbind();
}

} // namespace omega
