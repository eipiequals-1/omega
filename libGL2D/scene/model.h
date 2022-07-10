#ifndef LIBGL2D_SCENE_MODEL_H
#define LIBGL2D_SCENE_MODEL_H

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <string>
#include <vector>

#include "libGL2D/core/using.h"
#include "libGL2D/gfx/shader.h"
#include "libGL2D/gfx/texture/mesh.h"

namespace libgl {

class Model {
   public:
	Model(const std::string &filepath);

	void Render(Shader &shader);

   private:
	void ProcessNode(aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<MeshTexture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &type_name);

	std::vector<Mesh> meshes_;
	std::vector<MeshTexture> textures_;
	std::string directory_;
};

}  // namespace libgl

#endif  // LIBGL2D_SCENE_MODEL_H