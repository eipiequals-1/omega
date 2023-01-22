#include "editor/editor_layer.hpp"
#include "omega/core/core.hpp"
#include "omega/sound/sound.hpp"

class EditorApplication : public omega::core::Application {
  public:
    EditorApplication(const omega::core::ApplicationConfig &config) : omega::core::Application::Application(config) {
        push_layer(new omega::EditorLayer());
    }
};

int main() {
    omega::core::ApplicationConfig config;
    config.width = 1920;
    config.height = 1080;
    config.title = "Omega Engine";
    EditorApplication *editor = new EditorApplication(config);
    editor->run();
    delete editor;
    return 0;
}
