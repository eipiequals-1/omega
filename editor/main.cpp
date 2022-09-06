#include "editor/editor_layer.h"
#include "omega/core/core.h"

namespace editor {

class EditorApplication : public omega::core::Application {
  public:
    EditorApplication(const omega::core::ApplicationConfig &config) : omega::core::Application::Application(config) {
        push_layer(new EditorLayer());
    }
};
} // namespace editor

int main() {
    omega::core::ApplicationConfig config;
    config.width = 1920;
    config.height = 1080;
    config.title = "Omega Engine";
    editor::EditorApplication *editor = new editor::EditorApplication(config);
    editor->run();
    delete editor;
    return 0;
}