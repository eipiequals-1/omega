#include "scene.hpp"

#include "lib/imgui/imgui.h"
#include "omega/gfx/frame_buffer.hpp"
#include "omega/gfx/gl.hpp"
#include "omega/scene/orthographic_camera.hpp"
#include "omega/scene/imgui.hpp"
#include "omega/util/std.hpp"

Scene::Scene() : camera(0.0f, 1920.0f, 0.0f, 1080.0f) {
    framebuffer = omega::util::create_uptr<omega::gfx::FrameBuffer>(1920, 1080);
}

void Scene::render() {
    ImGui::Begin("Scene");
    
    // render to framebuffer first
    framebuffer->bind();
    // resize framebuffer if needed
    ImVec2 new_size = ImGui::GetContentRegionAvail();
    if (new_size.x != framebuffer->get_width() || new_size.y != framebuffer->get_height()) {
        framebuffer->resize(new_size.x, new_size.y);
    }

    omega::gfx::set_clear_color(1.0f, 1.0f, 1.0f, 1.0f);
    omega::gfx::clear_buffer(OMEGA_GL_COLOR_BUFFER_BIT);

    omega::gfx::FrameBuffer::unbind();

    // add framebuffer color attachment to viewport
    uint64_t tex_id = framebuffer->get_color_buffer()->get_renderer_id();
    ImGui::Image(reinterpret_cast<void*>(tex_id), ImVec2{(float)framebuffer->get_width(), (float)framebuffer->get_height()});
    ImGui::End();
}

