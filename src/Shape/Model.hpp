//
// Created by daftmat on 02/05/19.
//

#ifndef OPENGLTUTO_MODEL_HPP
#define OPENGLTUTO_MODEL_HPP

#include "../../src/Shape/Mesh.hpp"
#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

unsigned int TextureFromFile(char const * path, const std::string &directory, bool gamma = false);
unsigned int TextureFromFile(const std::string &path, bool gamma = false);

class Model {
    std::string directory;

    std::vector<Texture> textures_loaded;

    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    glm::mat4 transform;

public:
    std::vector<Mesh> meshes;

    Model() = default;
    Model(char *path) {loadModel(path);}

    void setTransform(const glm::mat4 &t) { transform=t; }
    const glm::mat4 & getTransform() { return transform; }

    void Draw(Shader shader);
};

#endif //OPENGLTUTO_MODEL_HPP
