#include "layer_stack.hpp"

namespace omega::scene {

LayerStack::LayerStack() {
}

LayerStack::~LayerStack() {
    for (auto &layer : layers) {
        if (layer != nullptr) {
            delete layer;
        }
        layer = nullptr;
    }
}

void LayerStack::render(f32 dt) {
    for (auto itr = layers.begin(); itr != layers.end(); ++itr) {
        (*itr)->render(dt);
    }
}

void LayerStack::update(f32 dt) {
    for (auto itr = layers.rbegin(); itr != layers.rend(); ++itr) {
        (*itr)->update(dt);
    }
}

void LayerStack::input(f32 dt) {
    for (auto itr = layers.rbegin(); itr != layers.rend(); ++itr) {
        (*itr)->input(dt);
    }
}

void LayerStack::push_layer(Layer *layer) {
    layers.push_back(layer);
}

void LayerStack::pop_layer() {
    layers.pop_back();
}

} // namespace omega
