#include "model.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "omega/gfx/gl.hpp"

namespace omega::scene {

static uint32_t texture_from_file(const std::string &filepath) {
    uint32_t id = 0;
    SDL_Surface *surf = IMG_Load(filepath.c_str());
    if (surf == nullptr) {
        util::error("IMG error: Error loading '{}'\n IMG Error: '{}'",
                    filepath,
                    IMG_GetError());
        return id;
    }
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // free SDL surface
    SDL_FreeSurface(surf);
    surf = nullptr;
    return id;
}

static Assimp::Importer importer;

Model::Model(const std::string &filepath) {
    const aiScene *scene =
        importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (scene == nullptr ||
        scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        scene->mRootNode == nullptr) {
        
        util::error("Error: Assimp: '{}'", importer.GetErrorString());
        return;
    }
    directory = filepath.substr(0, filepath.find_last_of('/'));
    process_node(scene->mRootNode, scene);
}

void Model::render(gfx::Shader &shader) {
    for (auto &mesh : meshes) {
        mesh.render(shader);
    }
}

void Model::process_node(aiNode *node, const aiScene *scene) {
    // process all the node's meshes
    for (uint32_t i = 0; i < node->mNumMeshes; ++i) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(process_mesh(mesh, scene));
    }
    // process children recursively
    for (uint32_t i = 0; i < node->mNumChildren; ++i) {
        process_node(node->mChildren[i], scene);
    }
}

static glm::vec3 to_vec3(const aiVector3D& v) {
    return glm::vec3(v.x, v.y, v.z);
}

Mesh Model::process_mesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<MeshVertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<MeshTexture> textures;

    // process vertices
    for (uint32_t i = 0; i < mesh->mNumVertices; ++i) {
        MeshVertex vertex;
        // positions
        vertex.position = to_vec3(mesh->mVertices[i]);
        // normals
        if (mesh->HasNormals()) {
            vertex.normal = to_vec3(mesh->mNormals[i]);
        }
        if (mesh->mTextureCoords[0]) {
            // tex coords
            vertex.tex_coords = to_vec3(mesh->mTextureCoords[0][i]);
            /* // tangent */
            /* vertex.tangent = to_vec3(mesh->mTangents[i]); */
            /* // bitangent */
            /* vertex.bitangent = to_vec3(mesh->mBitangents[i]); */
        } else {
            vertex.tex_coords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }
    // process vertex indices
    for (uint32_t i = 0; i < mesh->mNumFaces; ++i) {
        aiFace &face = mesh->mFaces[i];
        // get all indices on each face and push_back to indices vector
        for (uint32_t j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }
    // process materials
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        // diffuse
        std::vector<MeshTexture> diffuse_maps =
            load_material_textures(material,
                                   aiTextureType_DIFFUSE,
                                   "texture_diffuse");
        textures.insert(
            textures.end(), diffuse_maps.begin(), diffuse_maps.end());
        // specular
        std::vector<MeshTexture> specular_maps =
            load_material_textures(material,
                                   aiTextureType_SPECULAR,
                                   "texture_specular");
        textures.insert(
            textures.end(), specular_maps.begin(), specular_maps.end());
        /* // normal */
        /* std::vector<MeshTexture> normal_maps = load_material_textures(material, aiTextureType_HEIGHT, "texture_normal"); */
        /* textures.insert(textures.end(), normal_maps.begin(), normal_maps.end()); */
        /* // height */
        /* std::vector<MeshTexture> height_maps = load_material_textures(material, aiTextureType_AMBIENT, "texture_height"); */
        /* textures.insert(textures.end(), height_maps.begin(), height_maps.end()); */
    }
    // return mesh object
    omega::util::print("{}", __LINE__);
    return Mesh(vertices, indices, textures);
}

std::vector<MeshTexture> Model::load_material_textures(
    aiMaterial *mat,
    aiTextureType type,
    const std::string &type_name) {
    
    std::vector<MeshTexture> textures;
    for (uint32_t i = 0; i < mat->GetTextureCount(type); ++i) {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if the texture was not already loaded
        bool skip = false;
        for (uint32_t j = 0; j < this->textures.size(); ++j) {
            if (std::strcmp(this->textures[j].path.c_str(), str.C_Str()) == 0) {
                textures.push_back(this->textures[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {
            MeshTexture texture;
            std::string path = directory + "/" + std::string(str.C_Str());
            texture.id = texture_from_file(path);
            texture.type = type_name;
            texture.path = path;
            textures.push_back(texture);
            this->textures.push_back(texture);
        }
    }
    omega::util::print("{}", __LINE__);
    return textures;
}

} // namespace omega::scene
