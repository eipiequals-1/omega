#include "layer_stack.h"

namespace omega {

LayerStack::LayerStack() {
}

LayerStack::~LayerStack() {
	for (auto &layer : layers_) {
		if (layer != nullptr) {
			delete layer;
		}
		layer = nullptr;
	}
}

void LayerStack::Render(float dt) {
	for (auto itr = layers_.begin(); itr != layers_.end(); ++itr) {
		(*itr)->Render(dt);
	}
}

void LayerStack::Update(float dt) {
	for (auto itr = layers_.rbegin(); itr != layers_.rend(); ++itr) {
		(*itr)->Update(dt);
	}
}

void LayerStack::Input(float dt) {
	for (auto itr = layers_.rbegin(); itr != layers_.rend(); ++itr) {
		(*itr)->Input(dt);
	}
}

void LayerStack::PushLayer(Layer *layer) {
	layers_.push_back(layer);
}

void LayerStack::PopLayer() {
	layers_.pop_back();
}

}  // namespace omega