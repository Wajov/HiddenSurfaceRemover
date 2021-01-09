#include "Model.h"

Model::Model(const std::string &path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Failed to load model:" << std::endl << importer.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode, scene);

    float xMin, xMax, yMin, yMax, zMin, zMax;
    xMin = yMin = zMin = FLT_MAX;
    xMax = yMax = zMax = -FLT_MAX;
    for (Mesh &mesh : meshes) {
        float xMinTemp, xMaxTemp, yMinTemp, yMaxTemp, zMinTemp, zMaxTemp;
        mesh.coordinateRange(xMinTemp, xMaxTemp, yMinTemp, yMaxTemp, zMinTemp, zMaxTemp);
        xMin = std::min(xMin, xMinTemp);
        xMax = std::max(xMax, xMaxTemp);
        yMin = std::min(yMin, yMinTemp);
        yMax = std::max(yMax, yMaxTemp);
        zMin = std::min(zMin, zMinTemp);
        zMax = std::max(zMax, zMaxTemp);
    }
    glm::vec3 center((xMin + xMax) / 2, (yMin + yMax) / 2, (zMin + zMax) / 2);
    for (Mesh &mesh : meshes)
        mesh.recenter(center);
}

Model::~Model() {}

void Model::render(ZBuffer *zBuffer) {
    for (Mesh &mesh : meshes)
        mesh.render(zBuffer);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
        meshes.push_back(processMesh(scene->mMeshes[node->mMeshes[i]]));
    for (unsigned int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene);
}

Mesh Model::processMesh(aiMesh *mesh) {
    std::vector<Vertex> vertices;
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        glm::vec3 position(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        glm::vec3 normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        vertices.push_back(Vertex(position, normal));
    }

    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
            indices.push_back(mesh->mFaces[i].mIndices[j]);

    return Mesh(vertices, indices);
}
