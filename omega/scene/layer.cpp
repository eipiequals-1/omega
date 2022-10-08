#include "layer.h"

namespace omega::scene {

Layer::Layer(const std::string &name, bool imgui) : name(name), imgui(imgui) {
}

Layer::~Layer() {
}

} // namespace omega