#ifndef OMEGA_SCENE_IMGUI_HPP
#define OMEGA_SCENE_IMGUI_HPP

#include <functional>

#include "lib/imgui/imgui.h"

namespace ImGui {

/**
 * Enable ImGui Dockspace mode
 * @param open if the dockspace is open
*/
void EnableDockspace(bool open, std::function<void()> render);

} // namespace ImGui

#endif // OMEGA_SCENE_IMGUI_HPP 
