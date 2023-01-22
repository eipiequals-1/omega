#include "scene_hierarchy.hpp"

#include <cstring>
#include <functional>
#include <string>

#include "lib/imgui/imgui.h"

namespace omega {

template <typename ComponentType>
static void render_component(const std::string &label, scene::Entity entity, std::function<void(ComponentType &)> render) {
    if (entity.has_component<ComponentType>()) {
        if (ImGui::TreeNodeEx((void *)typeid(ComponentType).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "%s", label.c_str())) {
            ComponentType &comp = entity.get_component<ComponentType>();
            render(comp);
            ImGui::TreePop();
        }
    }
}

SceneHierarchy::SceneHierarchy(util::sptr<scene::Scene> scene) : scene(scene) {
}

SceneHierarchy::~SceneHierarchy() {
}

void SceneHierarchy::render() {
    static bool b = true;
    ImGui::ShowDemoWindow(&b);
    ImGui::Begin("Scene Hierarchy");

    if (scene != nullptr) {
        if (ImGui::TreeNode(scene->get_name().c_str())) {
            scene->get_registry().each([&](auto entity_id) {
                scene::Entity entity(entity_id, &scene->get_registry());
                draw_entity_node(entity);
            });
            ImGui::TreePop();
        }

        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
            selected_entity = {};
        }
        // create new entities
        if (ImGui::BeginPopupContextWindow(0, 1, false)) {
            if (ImGui::MenuItem("Create New Entity"))
                scene->create_entity("New Entity");
            ImGui::EndPopup();
        }
    }

    ImGui::End();

    // properties panel
    ImGui::Begin("Properties");

    if (selected_entity) {
        // tag component
        render_component<scene::TagComponent>("Tag", selected_entity, [](scene::TagComponent &tag) {
            char buffer[128];
            strcpy(buffer, tag.tag.c_str());
            if (ImGui::InputText("###", buffer, sizeof(buffer))) {
                tag.tag = std::string(buffer);
            }
        });

        // transform component
        render_component<scene::TransformComponent>("Transform", selected_entity, [](scene::TransformComponent &transform) {
            ImGui::DragFloat3("Position", glm::value_ptr(transform.position), 0.1f);
            ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale), 0.1f);
            ImGui::DragFloat3("Rotation", glm::value_ptr(transform.rotation), 0.1f);
        });

        // sprite component
        render_component<scene::SpriteComponent>("Sprite", selected_entity, [](scene::SpriteComponent &sprite) {
            // show sprite dimensions
            ImGui::Text("Dimensions: %u x %u", sprite.texture->get_width(), sprite.texture->get_height());
            // change sprite color
            ImGui::ColorEdit4("Color", glm::value_ptr(sprite.color));
        });

        // camera component
        render_component<scene::CameraComponent>("Camera", selected_entity, [](scene::CameraComponent &camera) {
            ImGui::Checkbox("Primary", &camera.primary);

            const char *types[] = {"Orthographic", "Perspective"};
            const char *current_type = camera.camera_type == scene::CameraComponent::ProjectionType::orthographic ? types[0] : types[1];
            // toggle camera type
            if (ImGui::BeginCombo("Projection Type", current_type, 0)) {
                for (int n = 0; n < 2; n++) {
                    const bool is_selected = (current_type == types[n]);
                    if (ImGui::Selectable(types[n], is_selected)) {
                        current_type = types[n];
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            camera.camera_type = current_type == types[0] ? scene::CameraComponent::ProjectionType::orthographic : scene::CameraComponent::ProjectionType::perspective;

            // orthographic camera
            if (camera.camera_type == scene::CameraComponent::ProjectionType::orthographic) {
                // set camera position
                ImGui::DragFloat3("Position", glm::value_ptr(camera.ortho.position));
                // set camera rotation
                float rotation = camera.ortho.get_rotation();
                ImGui::DragFloat("Rotation", &rotation);
                camera.ortho.set_rotation(rotation);

                // set camera projection

                // aspect ratio
                glm::vec3 aspect = glm::vec3(camera.ortho.get_width(), camera.ortho.get_height(), camera.ortho.get_depth());
                if (ImGui::DragFloat3("Scale (X, Y, Z)", glm::value_ptr(aspect))) {
                    // set new orthographic projection
                    camera.ortho.set_projection(
                        -aspect.x * 0.5f,
                        aspect.x * 0.5f,
                        -aspect.y * 0.5f,
                        aspect.y * 0.5f,
                        -aspect.z * 0.5f,
                        aspect.z * 0.5f);
                }
            } else {
            }
        });
    }

    ImGui::End();
}

void SceneHierarchy::draw_entity_node(scene::Entity ent) {
    scene::TagComponent &tag = ent.get_component<scene::TagComponent>();

    ImGuiTreeNodeFlags flags = (ent == selected_entity) ? ImGuiTreeNodeFlags_Selected : 0;
    flags |= ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;

    if (ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)ent, flags, "%s", tag.tag.c_str())) {
        selected_entity = ent;
        ImGui::TreePop();
    }
}

} // namespace omega
