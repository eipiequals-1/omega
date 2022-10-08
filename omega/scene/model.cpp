#include "model.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace omega::scene {

static u32 texture_from_file(const std::string &filepath) {
    u32 id = 0;
    SDL_Surface *surf = IMG_Load(filepath.c_str());
    if (surf == nullptr) {
        util::log("IMG error: Error loading '", filepath, "': ", IMG_GetError());
        return id;
    }
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // if rendered smaller, use giver filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);               // if rendered larger, use given filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);                   // continue closest color to edge
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // free SDL surface
    SDL_FreeSurface(surf);
    surf = nullptr;
    return id;
}

Model::Model(const std::string &filepath) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr) {
        util::log("Error: Assimp: ", importer.GetErrorString());
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
    for (u32 i = 0; i < node->mNumMeshes; ++i) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(process_mesh(mesh, scene));
    }
    // process children recursively
    for (u32 i = 0; i < node->mNumChildren; ++i) {
        process_node(node->mChildren[i], scene);
    }
}

Mesh Model::process_mesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<MeshVertex> vertices;
    std::vector<u32> indices;
    std::vector<MeshTexture> textures;

    glm::vec3 vec;
    // process vertices
    for (u32 i = 0; i < mesh->mNumVertices; ++i) {
        MeshVertex vertex;
        // positions
        vec.x = mesh->mVertices[i].x;
        vec.y = mesh->mVertices[i].y;
        vec.z = mesh->mVertices[i].z;
        vertex.position = vec;
        // normals
        if (mesh->HasNormals()) {
            vec.x = mesh->mNormals[i].x;
            vec.y = mesh->mNormals[i].y;
            vec.z = mesh->mNormals[i].z;
            vertex.normal = vec;
        }
        if (mesh->mTextureCoords[0]) {
            // tex coords
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.tex_coords = glm::vec2(vec.x, vec.y);
            // tangent
            vec.x = mesh->mTangents[i].x;
            vec.y = mesh->mTangents[i].y;
            vec.z = mesh->mTangents[i].z;
            vertex.tangent = vec;
            // bitangent
            vec.x = mesh->mBitangents[i].x;
            vec.y = mesh->mBitangents[i].y;
            vec.z = mesh->mBitangents[i].z;
            vertex.bitangent = vec;
        } else {
            vertex.tex_coords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }
    // process vertex indices
    for (u32 i = 0; i < mesh->mNumFaces; ++i) {
        aiFace &face = mesh->mFaces[i];
        // get all indices on each face and push_back to indices vector
        for (u32 j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }
    // process materials
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    // diffuse
    std::vector<MeshTexture> diffuse_maps = load_material_textures(material, aiTextureType_DIFFUSE, "textureDiffuse");
    textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());
    // specular
    std::vector<MeshTexture> specular_maps = load_material_textures(material, aiTextureType_SPECULAR, "textureDiffuse");
    textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());
    // normal
    std::vector<MeshTexture> normal_maps = load_material_textures(material, aiTextureType_HEIGHT, "textureNormal");
    textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());
    // height
    std::vector<MeshTexture> height_maps = load_material_textures(material, aiTextureType_AMBIENT, "textureHeight");
    textures.insert(textures.end(), height_maps.begin(), height_maps.end());
    // return mesh object
    return Mesh(vertices, indices, textures);
}

std::vector<MeshTexture> Model::load_material_textures(aiMaterial *mat, aiTextureType type, const std::string &type_name) {
    std::vector<MeshTexture> textures;
    for (u32 i = 0; i < mat->GetTextureCount(type); ++i) {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if the texture was not already loaded
        bool skip = false;
        for (u32 j = 0; j < textures.size(); ++j) {
            if (std::strcmp(textures[j].path.c_str(), str.C_Str()) == 0) {
                textures.push_back(textures[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {
            MeshTexture texture;
            texture.id = texture_from_file(std::string(str.C_Str()));
            texture.type = type_name;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures.push_back(texture);
        }
    }
    return textures;
}

} // namespace omega::scene