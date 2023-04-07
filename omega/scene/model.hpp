#ifndef OMEGA_SCENE_MODEL_HPP
#define OMEGA_SCENE_MODEL_HPP

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#include <string>
#include <vector>

#include "omega/gfx/shader.hpp"
#include "omega/gfx/texture/mesh.hpp"

namespace omega::scene {

using namespace omega::gfx::texture;

class Model {
public:
    Model(const std::string &filepath);

    void render(gfx::Shader &shader);

private:
    void process_node(aiNode *node, const aiScene *scene);
    Mesh process_mesh(aiMesh *mesh, const aiScene *scene);
    std::vector<MeshTexture> load_material_textures(
        aiMaterial *mat,
        aiTextureType type,
        const std::string &type_name);

    std::vector<Mesh> meshes;
    std::vector<MeshTexture> textures;
    std::string directory;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_MODEL_HPP
