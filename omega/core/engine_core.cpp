#include "engine_core.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3_image/SDL_image.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl3.h>
#include <implot/implot.h>

#include "SDL3/SDL_init.h"
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

    ImGui_ImplSDL3_InitForOpenGL(window->get_native_window(),
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
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    ImPlot::DestroyContext();
}

void begin_imgui_frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
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
    util::time::init();
    return running;
}

void quit(bool imgui) {
    if (imgui) {
        quit_imgui();
        util::info("Successfully quit ImGui.");
    }
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
    SDL_Quit();
    util::info("Successfully closed libraries.");
}

} // namespace omega::core
