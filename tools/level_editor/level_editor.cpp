#include <iostream>

#include "lib/imgui/imgui.h"

#include "omega/core/core.hpp"
#include "omega/gfx/gfx.hpp"
#include "omega/scene/orthographic_camera.hpp"

using namespace omega::core;
using namespace omega;

int main() {
	AppConfig app_config;
    app_config.imgui = true;
	App *app = new App(app_config);


	app->setup = [&](Globals *globals) {
		(void)globals;
	};

	app->render = [&](float dt, Globals *globals) {
		(void)dt;
		(void)globals;
		gfx::set_clear_color(0.05f, 0.05f, 0.05f, 1.0f);
		gfx::clear_buffer(OMEGA_GL_COLOR_BUFFER_BIT);

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

