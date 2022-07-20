#include "editor/editor.h"

int main() {
	omega::ApplicationConfig config;
	config.width = 1920;
	config.height = 1080;
	config.title = "Omega Engine";
	editor::EditorApplication *editor = new editor::EditorApplication(config);
	editor->Run();
	return 0;
}