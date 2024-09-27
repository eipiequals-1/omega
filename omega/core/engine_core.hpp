#ifndef OMEGA_CORE_ENGINECORE_HPP
#define OMEGA_CORE_ENGINECORE_HPP

#include <functional>

#include "omega/core/window.hpp"

namespace omega::core {

void setup_imgui(Window *window);

void quit_imgui();

void begin_imgui_frame();

void end_imgui_frame(Window *window);

bool init();

void quit(bool imgui);

} // namespace omega::core

#endif // OMEGA_CORE_ENGINECORE_HPP
