#include <iostream>

#include "lib/imgui/imgui.h"

#include "omega/core/core.hpp"
#include "omega/gfx/gfx.hpp"
#include "omega/scene/orthographic_camera.hpp"

using namespace omega::core;
using namespace omega;

int main() {
    // configure application
	AppConfig app_config;
    app_config.title = "Omega - Level Editor";
    app_config.width = 1920;
    app_config.height = 1080;
    app_config.imgui = true;
    // create application
	App *app = new App(app_config);


	app->setup = [&](Globals *globals) {
		(void)globals;
	};

	app->render = [&](float dt, Globals *globals) {
		(void)dt;
		(void)globals;
		gfx::set_clear_color(0.05f, 0.05f, 0.05f, 1.0f);
		gfx::clear_buffer(OMEGA_GL_COLOR_BUFFER_BIT);

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
    
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New", "Ctrl+N")) {
                }
                if (ImGui::MenuItem("Open", "Ctrl+O")) {
                }
                if (ImGui::MenuItem("Exit", "Ctrl+Q")) {
                    
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::End();


        ImGui::Begin("Scene");

        ImGui::End();

        ImGui::ShowDemoWindow();
	};

	app->input = [&](float dt, Globals *globals, events::InputManager *input) -> bool {
		(void)dt;
		(void)globals;
		if (input->get_key_manager().key_pressed(events::Key::k_escape)) return true;
		return false;
	};

	app->run();

	delete app;
	return 0;
}

