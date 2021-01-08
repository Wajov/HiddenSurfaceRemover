#ifndef MODEL_H
#define MODEL_H

#include <climits>
#include <iostream>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "ZBuffer.h"

class Model {
private:
    std::vector<Mesh> meshes;
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh);

public:
    Model(const std::string &path);
    ~Model();
    void render(ZBuffer *zBuffer);
};

#endif