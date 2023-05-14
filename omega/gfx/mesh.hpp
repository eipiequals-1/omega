#ifndef OMEGA_GFX_MESH_HPP
#define OMEGA_GFX_MESH_HPP

#include "omega/gfx/gl.hpp"
#include "omega/gfx/index_buffer.hpp"
#include "omega/gfx/shader.hpp"
#include "omega/gfx/vertex_buffer.hpp"
#include "omega/gfx/vertex_buffer_layout.hpp"
#include "omega/gfx/vertex_array.hpp"
#include "omega/util/std.hpp"

#include <span>

namespace omega::gfx {

class Mesh {
  public:
    explicit Mesh(size_t size,
                  const VertexBufferLayout &layout);
    ~Mesh() = default;

    template <typename T>
    void set_vertices(const std::span<T> vertices) {
        vbo->sub_data(0, vertices.size() * sizeof(T), vertices.data());
        num_vertices = vertices.size();
    }

    template <typename T>
    void set_indices(const std::span<T> indices) {
        ibo = util::create_uptr<IndexBuffer>(indices.size());
        ibo->sub_data(0, indices.size() * sizeof(T), indices.data());
    }

    void render(Shader &shader, macro primitive);

  private:
    util::uptr<IndexBuffer> ibo = nullptr;
    util::uptr<VertexBuffer> vbo = nullptr;
    util::uptr<VertexArray> vao = nullptr;

    uint32_t num_vertices = 0;
};

} // namespace omega::gfx

#endif // OMEGA_GFX_MESH_HPP
