#include "mesh.h"

namespace libgl {

Mesh::Mesh(std::vector<MeshVertex> vertices, std::vector<uint32_t> indices, std::vector<MeshTexture> textures) {
	vertices_ = vertices;
	indices_ = indices;
	textures_ = textures;
	SetupMesh();
}

void Mesh::Render(Shader& shader) {
	uint32_t diffuse_num = 1;
	uint32_t specular_num = 1;
	for (uint32_t i = 0; i < textures_.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string name = textures_[i].type;
		if (name == "textureDiffuse") {
			number = std::to_string(diffuse_num++);
		} else if (name == "textureSpecular") {
			number = std::to_string(specular_num++);
		}
		shader.SetUniform1i(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures_[i].id);
	}
	glActiveTexture(GL_TEXTURE0);
	// draw mesh
	shader.Bind();
	ibo_->Bind();
	vao_->Bind();
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, nullptr);
	vao_->Unbind();
	ibo_->Unbind();
	shader.Unbind();
}

void Mesh::SetupMesh() {
	vao_ = CreateUptr<VertexArray>();
	vbo_ = CreateUptr<VertexBuffer>(vertices_.data(), vertices_.size() * sizeof(MeshVertex));
	ibo_ = CreateUptr<IndexBuffer>(indices_.data(), indices_.size());
	VertexBufferLayout layout;
	layout.Push(GL_FLOAT, 3);
	layout.Push(GL_FLOAT, 3);
	layout.Push(GL_FLOAT, 2);
	vao_->AddBuffer(*vbo_, layout);
	vao_->Unbind();
}

}  // namespace libgl