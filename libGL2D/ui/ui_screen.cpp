#include "ui_screen.h"

namespace libgl {

UIScreen::UIScreen() {
}

UIScreen::~UIScreen() {
	for (auto &btn : buttons_) {
		if (btn != nullptr) delete btn;
		btn = nullptr;
	}
}

void UIScreen::Update(const glm::vec2 &mouse_pos) {
	for (auto &btn : buttons_) {
		btn->SetHover(false);
		if (btn->ContainsPoint(mouse_pos)) {
			btn->SetHover(true);
		}
	}
}

void UIScreen::PushButton(Button *button) {
	buttons_.push_back(button);
}

void UIScreen::HandleButtons() {
	if (InputManager::Instance().MouseButtonJustReleased(MouseButton::kMouseLeft)) {
		for (auto &btn : buttons_) {
			if (btn->GetHover()) {
				btn->OnClick();
			}
		}
	}
}

}  // namespace libgl
