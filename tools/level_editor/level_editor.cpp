#include <iostream>

#include "omega/core/core.hpp"
#include "omega/gfx/gfx.hpp"
#include "omega/scene/orthographic_camera.hpp"

#include "omega/scene/imgui.hpp"
#include "tools/level_editor/scene.hpp"

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

    bool should_quit = false;
    Scene scene;

    app->setup = [&](Globals *globals) {
        (void)globals;
        ImGui::StyleColorsDark();
    };

    app->render = [&](float dt, Globals *globals) {
        (void)dt;
        (void)globals;
        gfx::set_clear_color(0.05f, 0.05f, 0.05f, 1.0f);
        gfx::clear_buffer(OMEGA_GL_COLOR_BUFFER_BIT);

        ImGui::EnableDockspace(true, [&]() {
            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("New", "Ctrl+N")) {
                    }
                    if (ImGui::MenuItem("Open", "Ctrl+O")) {
                    }
                    if (ImGui::MenuItem("Exit", "Ctrl+Q")) {
                        should_quit = true;
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
        });

        scene.render();

        ImGui::Begin("Properties");
        ImGui::End();

        ImGui::Begin("Tilesets");
        ImGui::End();
        ImGui::Begin("Layers");
        ImGui::End();

        /* ImGui::ShowDemoWindow(); */
    };

    app->input = [&](float dt, Globals *globals, events::InputManager *input) -> bool {
        (void)dt;
        (void)globals;
        if (input->get_key_manager().key_pressed(events::Key::k_escape)) should_quit = true;
        return should_quit;
    };
    app->update = [&](float dt, Globals* globals) -> bool {
        (void)dt;
        (void)globals;
        return should_quit;
    };

    app->run();

    delete app;
    return 0;
}

