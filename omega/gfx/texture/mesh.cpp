#include "mesh.hpp"

#include "omega/gfx/gl.hpp"

namespace omega::gfx::texture {

Mesh::Mesh(
    const std::vector<MeshVertex>& vertices,
    const std::vector<uint32_t>& indices,
    const std::vector<MeshTexture>& textures
) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    setup_mesh();
}

void Mesh::render(Shader &shader) {
    shader.bind();
    uint32_t diffuse_num = 1;
    uint32_t specular_num = 1;
    for (uint32_t i = 0; i < textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse") {
            number = std::to_string(diffuse_num++);
        } else if (name == "texture_specular") {
            number = std::to_string(specular_num++);
        }
        shader.set_uniform_1i(name + number, i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    // draw mesh
    ibo->bind();
    vao->bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    vao->unbind();
    ibo->unbind();
    shader.unbind();
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setup_mesh() {
    vao = util::create_uptr<VertexArray>();
    vbo = util::create_uptr<VertexBuffer>(
        vertices.data(), vertices.size() * sizeof(MeshVertex)
    );

    ibo = util::create_uptr<IndexBuffer>(indices.data(), indices.size());
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 3); // position
    layout.push(GL_FLOAT, 3); // normal
    layout.push(GL_FLOAT, 2); // texture coords
    vao->add_buffer(*vbo, layout);
    vao->unbind();
}

} // namespace omega
