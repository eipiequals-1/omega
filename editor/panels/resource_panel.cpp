#include "resource_panel.h"

#include "lib/imgui/imgui.h"

#include <cstring>

namespace omega {

ResourcePanel::ResourcePanel() {
    file_texture = gfx::texture::Texture::create_from_file("./editor/res/ui/file_icon.png");
    directory_texture = gfx::texture::Texture::create_from_file("./editor/res/ui/directory_icon.png");
}

ResourcePanel::~ResourcePanel() {
}

void ResourcePanel::render() {
    ImGui::Begin("Project");

    static float padding = 16.0f;
    static float thumbnail_size = 64.0f;
    float cell_size = thumbnail_size + padding;

    float panel_width = ImGui::GetContentRegionAvail().x;
    int column_count = (int)(panel_width / cell_size);
    if (column_count < 1)
        column_count = 1;

    ImGui::Columns(column_count, nullptr, false);

    ImGui::PushID("Textures");
    // ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
    ImGui::ImageButton(reinterpret_cast<ImTextureID>(directory_texture->get_renderer_id()), ImVec2{thumbnail_size, thumbnail_size}, ImVec2{0.0f, 0.0f}, ImVec2{1.0f, 1.0f});

    if (ImGui::BeginDragDropSource()) {
        ImGui::EndDragDropSource();
    }

    // ImGui::PopStyleColor();
    ImGui::TextWrapped("Textures");

    ImGui::NextColumn();

    ImGui::PopID();

    ImGui::Columns(1);

    ImGui::SliderFloat("Thumbnail Size", &thumbnail_size, 16, 512);
    ImGui::SliderFloat("Padding", &padding, 0, 32);

    ImGui::End();
}

} // namespace omega
