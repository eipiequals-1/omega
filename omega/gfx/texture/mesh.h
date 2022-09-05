#ifndef OMEGA_GFX_TEXTURE_MESH_H
#define OMEGA_GFX_TEXTURE_MESH_H

#include <GL/gl.h>

#include <string>
#include <vector>

#include "omega/gfx/index_buffer.h"
#include "omega/gfx/shader.h"
#include "omega/gfx/vertex_array.h"
#include "omega/gfx/vertex_buffer.h"
#include "omega/gfx/vertex_buffer_layout.h"
#include "omega/util/util.h"

namespace omega {

struct MeshVertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex_coords;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

struct MeshTexture {
	uint32_t id;
	std::string type;
	std::string path;
};

class Mesh {
   public:
	Mesh(std::vector<MeshVertex> vertices, std::vector<uint32_t> indices, std::vector<MeshTexture> textures);

	void Render(Shader &shader);

   private:
	void SetupMesh();

	std::vector<MeshVertex> vertices_;
	std::vector<uint32_t> indices_;
	std::vector<MeshTexture> textures_;

	uptr<VertexArray> vao_;
	uptr<VertexBuffer> vbo_;
	uptr<IndexBuffer> ibo_;
};

}  // namespace omega

#endif  // OMEGA_GFX_TEXTURE_MESH_H