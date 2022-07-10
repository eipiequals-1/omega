#ifndef LIBGL2D_GFX_TEXTURE_MESH_H
#define LIBGL2D_GFX_TEXTURE_MESH_H

#include <GL/gl.h>

#include <string>
#include <vector>

#include "libGL2D/core/using.h"
#include "libGL2D/gfx/index_buffer.h"
#include "libGL2D/gfx/shader.h"
#include "libGL2D/gfx/vertex_array.h"
#include "libGL2D/gfx/vertex_buffer.h"
#include "libGL2D/gfx/vertex_buffer_layout.h"
#include "libGL2D/physics/math.h"

namespace libgl {

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

	Uptr<VertexArray> vao_;
	Uptr<VertexBuffer> vbo_;
	Uptr<IndexBuffer> ibo_;
};

}  // namespace libgl

#endif  // LIBGL2D_GFX_TEXTURE_MESH_H