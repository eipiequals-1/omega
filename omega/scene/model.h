#ifndef OMEGA_SCENE_MODEL_H
#define OMEGA_SCENE_MODEL_H

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <string>
#include <vector>

#include "omega/gfx/shader.h"
#include "omega/gfx/texture/mesh.h"
#include "omega/util/util.h"

namespace omega::scene {

using namespace omega::gfx::texture;

class Model {
  public:
    Model(const std::string &filepath);

    void render(Shader &shader);

  private:
    void process_node(aiNode *node, const aiScene *scene);
    Mesh process_mesh(aiMesh *mesh, const aiScene *scene);
    std::vector<MeshTexture> load_material_textures(aiMaterial *mat, aiTextureType type, const std::string &type_name);

    std::vector<Mesh> meshes;
    std::vector<MeshTexture> textures;
    std::string directory;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_MODEL_H