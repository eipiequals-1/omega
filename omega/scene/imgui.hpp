#ifndef OMEGA_SCENE_IMGUI_HPP
#define OMEGA_SCENE_IMGUI_HPP

#include <functional>

#include <imgui/imgui.h>

namespace ImGui {

/**
 * Enable ImGui Dockspace mode
 * @param render function that renders the Dockspace windows,
 * essentially the default imgui rendering
*/
void EnableDockspace(std::function<void()> render);

} // namespace ImGui

#endif // OMEGA_SCENE_IMGUI_HPP 
