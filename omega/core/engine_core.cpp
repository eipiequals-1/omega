#include "engine_core.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "lib/imgui/imgui.h"
#include "lib/imgui/imgui_impl_opengl3.h"
#include "lib/imgui/imgui_impl_sdl.h"
#include "lib/imgui/implot.h"
#include "omega/core/window.hpp"
#include "omega/util/time.hpp"

namespace omega::core {

void setup_imgui(Window *window) {
    // setup imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    /* ImGui::StyleColorsDark(); */

    ImGui_ImplSDL2_InitForOpenGL(window->get_native_window(),
                                 window->get_gl_context());
#ifdef EMSCRIPTEN
    const char version[] = "#version 100";
#else
    const char version[] = "#version 450";
#endif
    ImGui_ImplOpenGL3_Init(version);
}

void quit_imgui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    ImPlot::DestroyContext();
}

void begin_imgui_frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void end_imgui_frame(Window *window) {
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize =
        ImVec2((f32)window->get_width(), (f32)window->get_height());

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool init() {
    bool running = true;
    // init TTF_Font
    if (TTF_Init() != 0) {
        util::err("Unable to initialize SDL_ttf: '{}'", SDL_GetError());
        running = false;
    }
    util::time::init();
    return running;
}

void quit(bool imgui) {
    if (imgui) {
        quit_imgui();
        util::info("Successfully quit ImGui.");
    }
    SDL_Quit();
    TTF_Quit();
    util::info("Successfully closed libraries.");
}

} // namespace omega::core
