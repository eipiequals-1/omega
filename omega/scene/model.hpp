#ifndef OMEGA_SCENE_MODEL_HPP
#define OMEGA_SCENE_MODEL_HPP

#include "omega/gfx/gl.hpp"
#include "omega/gfx/index_buffer.hpp"
#include "omega/gfx/vertex_array.hpp"
#include "omega/gfx/vertex_buffer.hpp"
#include "omega/math/math.hpp"
#include "omega/util/std.hpp"
#include "omega/util/types.hpp"

namespace omega::scene {

class Model {
  public:
    Model(const std::string &file_path);
    Model(const std::vector<math::vec3> &pos,
          const std::vector<math::vec3> &norms,
          const std::vector<math::vec2> &tex,
          const std::vector<u32> &indices);
    ~Model();

    void render();

  private:
    void process_vertex(std::vector<std::string> &vertex_data,
                        std::vector<u32> &indices,
                        std::vector<math::vec2> &textures,
                        std::vector<math::vec3> &normals,
                        std::vector<math::vec2> &texture_array,
                        std::vector<math::vec3> &normal_array);

    util::uptr<gfx::IndexBuffer> ibo = nullptr;
    util::uptr<gfx::VertexArray> vao = nullptr;
    std::vector<util::uptr<gfx::VertexBuffer>> vbos;

    void create_mesh(const std::vector<math::vec3> &verts,
                     const std::vector<math::vec3> &norms,
                     const std::vector<math::vec2> &tex,
                     const std::vector<u32> &indices);

    template <typename T>
    void add_attribute_data(u32 attr_number,
                            gfx::macro type,
                            u32 count,
                            const std::vector<T> &data) {
        vbos.push_back(util::create_uptr<gfx::VertexBuffer>(
            data.data(), data.size() * sizeof(T)));
        vbos.back()->bind();
        glEnableVertexAttribArray(attr_number);
        glVertexAttribPointer(attr_number, count, type, false, 0, 0);
        // glDisableVertexAttribArray(attr_number);
        gfx::VertexBuffer::unbind();
    }
};

} // namespace omega::scene

#endif // OMEGA_SCENE_MODEL_HPP
