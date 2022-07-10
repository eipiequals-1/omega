#ifndef OMEGA_SCENE_MODEL_H
#define OMEGA_SCENE_MODEL_H

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <string>
#include <vector>

#include "omega/core/using.h"
#include "omega/gfx/shader.h"
#include "omega/gfx/texture/mesh.h"

namespace omega {

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

}  // namespace omega

#endif  // OMEGA_SCENE_MODEL_H