#ifndef OMEGA_GFX_RENDERER_DFR_HPP
#define OMEGA_GFX_RENDERER_DFR_HPP

#include "omega/gfx/frame_buffer.hpp"
#include "omega/gfx/shader.hpp"
#include "omega/gfx/vertex_array.hpp"
#include "omega/gfx/vertex_buffer.hpp"
#include "omega/util/std.hpp"

namespace omega::gfx::renderer {

class DeferredRenderer {
  public:
    DeferredRenderer(u32 width, u32 height,
                     const std::vector<FrameBufferAttachment> &attachments);
    virtual ~DeferredRenderer() = default;

    /**
     * render the geometry to the framebuffer
     * @param render - shader/pass specific code
     * */
    void geometry_pass(std::function<void ()> render);

    /**
     * shader specific that needs a quad
     * i.e. lighting pass, SSAO pass, blur pass, bloom pass, composite pass
     * */
    void quad_pass(std::function<void ()> render);

    util::uptr<FrameBuffer> gbuffer = nullptr;
    std::unordered_map<std::string, util::uptr<FrameBuffer>> framebuffers;

  private:

    // simple quad for lighting/composite pass
    util::uptr<VertexBuffer> vbo = nullptr;
    util::uptr<VertexArray> vao = nullptr;
};

} // namespace omega::gfx::renderer

#endif // OMEGA_GFX_RENDERER_DFR_HPP
