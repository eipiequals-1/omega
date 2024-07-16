#include "model.hpp"

#include <fstream>

#include "omega/gfx/gl.hpp"
#include "omega/gfx/index_buffer.hpp"
#include "omega/gfx/vertex_array.hpp"
#include "omega/gfx/vertex_buffer_layout.hpp"
#include "omega/util/log.hpp"
#include "omega/util/std.hpp"

namespace omega::scene {

Model::Model(const std::string &file_path) {
    std::ifstream f(file_path);
    if (!f) {
        util::err("Could not open file '{}'", file_path);
    }
    using Line = std::vector<std::string>;

    std::string line;

    std::vector<math::vec3> verts;
    std::vector<math::vec2> tex;
    std::vector<math::vec3> normals;
    std::vector<u32> indices;

    // sorted
    std::vector<math::vec2> tex_array;
    std::vector<math::vec3> normals_array;

    while (std::getline(f, line)) {
        Line current_line;
        util::split(line, current_line, " ");

        if (line.starts_with("v ")) {
            verts.push_back({
                std::stof(current_line[1]),
                std::stof(current_line[2]),
                std::stof(current_line[3]),
            });
        } else if (line.starts_with("vt ")) {
            tex.push_back({
                std::stof(current_line[1]),
                std::stof(current_line[2]),
            });
        } else if (line.starts_with("vn ")) {
            normals.push_back({
                std::stof(current_line[1]),
                std::stof(current_line[2]),
                std::stof(current_line[3]),
            });
        } else if (line.starts_with("f ")) {
            tex_array.resize(verts.size());
            normals_array.resize(verts.size());
            break;
        }
    }

    bool end = false;
    while (!end) {
        if (!line.starts_with("f ")) {
            end = !std::getline(f, line);
            continue;
        }

        // format -> "f v1/vt1/vn1 v2/v2/vn2 v3/vt3/vn3"
        // v -> vertex idx
        // vt -> texture coord idx
        // vn -> normal idx
        Line current_line;
        util::split(line, current_line, " ");
        Line vertex1;
        util::split(current_line[1], vertex1, "/");
        Line vertex2;
        util::split(current_line[2], vertex2, "/");
        Line vertex3;
        util::split(current_line[3], vertex3, "/");
        process_vertex(
            vertex1, indices, tex, normals, tex_array, normals_array);
        process_vertex(
            vertex2, indices, tex, normals, tex_array, normals_array);
        process_vertex(
            vertex3, indices, tex, normals, tex_array, normals_array);

        end = !std::getline(f, line);
    }

    // now load vbo, vao, ibo
    create_mesh(verts, normals_array, tex_array, indices);
}

Model::Model(const std::vector<math::vec3> &pos,
             const std::vector<math::vec3> &norms,
             const std::vector<math::vec2> &tex,
             const std::vector<u32> &indices) {
    create_mesh(pos, norms, tex, indices);
}

Model::~Model() {}

void Model::render() {
    vao->bind();
    // glEnableVertexAttribArray(0);
    // glEnableVertexAttribArray(1);
    // glEnableVertexAttribArray(2);
    for (auto &vbo : vbos) {
        vbo->bind();
    }
    ibo->bind();

    glDrawElements(GL_TRIANGLES, ibo->get_count(), GL_UNSIGNED_INT, 0);

    ibo->unbind();
    // glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);
    // glDisableVertexAttribArray(2);
    gfx::VertexArray::unbind();
}

void Model::process_vertex(std::vector<std::string> &vertex_data,
                           std::vector<u32> &indices,
                           std::vector<math::vec2> &textures,
                           std::vector<math::vec3> &normals,
                           std::vector<math::vec2> &texture_array,
                           std::vector<math::vec3> &normal_array) {
    i32 idx = std::stoi(vertex_data[0]) - 1;
    indices.push_back(idx);

    math::vec2 tex_coord = textures[std::stoi(vertex_data[1]) - 1];
    texture_array[idx] = {tex_coord.x, 1.0f - tex_coord.y};
    normal_array[idx] = normals[std::stoi(vertex_data[2]) - 1];
}

void Model::create_mesh(const std::vector<math::vec3> &verts,
                        const std::vector<math::vec3> &norms,
                        const std::vector<math::vec2> &tex,
                        const std::vector<u32> &indices) {
    // create vao
    vao = util::create_uptr<gfx::VertexArray>();
    vao->bind();

    add_attribute_data(0, GL_FLOAT, 3, verts); // position
    add_attribute_data(1, GL_FLOAT, 2, tex);   // tex coords
    add_attribute_data(2, GL_FLOAT, 3, norms); // norms

    // create ibo
    ibo = util::create_uptr<gfx::IndexBuffer>(indices.data(), indices.size());
}

} // namespace omega::scene
