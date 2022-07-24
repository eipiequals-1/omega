#include "editor/editor_layer.h"
#include "omega/core/application.h"

namespace editor {

class EditorApplication : public omega::Application {
   public:
	EditorApplication(const omega::ApplicationConfig &config) : omega::Application::Application(config) {
		PushLayer(new EditorLayer());
	}
};
}  // namespace editor

int main() {
	omega::ApplicationConfig config;
	config.width = 1920;
	config.height = 1080;
	config.title = "Omega Engine";
	editor::EditorApplication *editor = new editor::EditorApplication(config);
	editor->Run();
	delete editor;
	return 0;
}