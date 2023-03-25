#pragma once

#include <string>
#include <vector>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include "Mesh.h"
#include "Shader.h"
#include "assimp/material.h"

struct aiMaterial;
struct aiMesh;
struct aiScene;
struct aiNode;

class Model
{
public:
    Model(const std::string& path, bool gamma = false);
    ~Model();
    void Draw(Shader &shader);

    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;
private:
    void loadModel(const std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
};

