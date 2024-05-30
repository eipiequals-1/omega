#include "omega/core/app.hpp"
#include "omega/core/viewport.hpp"
#include "omega/scene/imgui.hpp"
#include "omega/gfx/gl.hpp"
#include "omega/scene/orthographic_camera.hpp"
#include "omega/ui/font.hpp"
#include "omega/ui/font_characters.hpp"
#include "omega/util/color.hpp"
#include "omega/util/std.hpp"
#include "omega/util/time.hpp"

using namespace omega::core;

#ifdef EMSCRIPTEN
const std::string ASSET_PATH = "../assets/";
#else
const std::string ASSET_PATH = "./assets/";
#endif

omega::sound::MusicID id;

class Game : public App {
public:
    Game(const AppConfig &config) : App::App(config), camera(0.0f, 1600.0f, 0.0f, 900.0f) {
        omega::gfx::enable_blending();
        globals->asset_manager.load_texture("tex", ASSET_PATH + "13.png");
        globals->asset_manager.load_texture("bg", ASSET_PATH + "bg.png");

        font = omega::util::create_uptr<omega::ui::Font>(ASSET_PATH + "font.png", omega::ui::font_characters::press_start_2p, 8, 8);
    }

    void render(f32 dt) override {
        omega::gfx::set_clear_color(0.0f, 0.0f, 0.0f, 1.0f);
        omega::gfx::clear_buffer(OMEGA_GL_COLOR_BUFFER_BIT);
        on_resize(window->get_width(), window->get_height());
        
        camera.recalculate_view_matrix();
        auto &sr = globals->shape_renderer;
        sr.set_view_projection_matrix(camera.get_view_projection_matrix());
        sr.begin();

        sr.color = omega::util::color::white * 0.8f;
        sr.rect(omega::math::rectf(0.0f, 0.0f, camera.get_width(), camera.get_height()));
        sr.color = omega::math::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        f32 t = omega::util::time::get_time<f32>();
        sr.rect(omega::math::rectf(100.0f + omega::math::sin(t) * 50.0f, 100.0f + omega::math::cos(t) * 50.0f, 100.0f, 100.0f));
        sr.end();

        auto &sb = globals->sprite_batch;
        sb.set_view_projection_matrix(camera.get_view_projection_matrix());
        sb.begin_render();

        sb.render_texture(globals->asset_manager.get_texture("tex"), 500.0f, 500.0f, 300.0f, 200.0f);
        sb.render_texture(globals->asset_manager.get_texture("bg"), 100.0f, 500.0f, 300.0f, 200.0f);


        font->render(sb, "A Big BAD WOLF!!!!", 15.0f, 15.0f, 60.0f, omega::util::color::blue);

        sb.end_render();

        ImGui::Begin("Test");
        ImGui::Text("%.2f", 1.0f / dt);
        ImGui::End();
    }
    omega::scene::OrthographicCamera camera;
    omega::util::uptr<omega::ui::Font> font = nullptr;
};

int main() {
    AppConfig config = AppConfig::from_config("./assets/config.toml");
    Game game(config);
    game.run();

    return 0;
}
