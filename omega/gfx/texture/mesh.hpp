#ifndef OMEGA_GFX_TEXTURE_MESH_HPP
#define OMEGA_GFX_TEXTURE_MESH_HPP

#include <string>
#include <vector>
#include <cstdint>
#include <span>

#include "omega/gfx/index_buffer.hpp"
#include "omega/gfx/shader.hpp"
#include "omega/gfx/vertex_array.hpp"
#include "omega/gfx/vertex_buffer.hpp"
#include "omega/gfx/vertex_buffer_layout.hpp"
#include "omega/util/std.hpp"

namespace omega::gfx::texture {

class Mesh {
  public:
    Mesh();

    template <typename T>
    void set_vertices(const std::span<T> *data) {}
    void render(Shader &shader);

  private:
    util::uptr<VertexArray> vao = nullptr;
    util::uptr<VertexBuffer> vbo = nullptr;
    util::uptr<IndexBuffer> ibo = nullptr;
};

} // namespace omega::gfx::texture

#endif // OMEGA_GFX_TEXTURE_MESH_HPP
