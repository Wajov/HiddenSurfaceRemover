#ifndef MODEL_H
#define MODEL_H

#include <cfloat>
#include <iostream>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <QImage>

#include "ZBuffer.h"

class Model {
private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    void processNode(aiNode *node, const aiScene *scene);
    void processMesh(aiMesh *mesh);

public:
    Model(const std::string &path);
    ~Model();
    QImage render(ZBuffer *zBuffer);
};

#endif