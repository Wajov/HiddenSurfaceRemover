#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) {
    this->vertices = vertices;
    this->indices = indices;
}

Mesh::~Mesh() {}

void Mesh::coordinateRange(float &xMin, float &xMax, float &yMin, float &yMax, float &zMin, float &zMax) {
    xMin = yMin = zMin = FLT_MAX;
    xMax = yMax = zMax = -FLT_MAX;
    for (Vertex &vertex : vertices) {
        xMin = std::min(xMin, vertex.position.x);
        xMax = std::max(xMax, vertex.position.x);
        yMin = std::min(yMin, vertex.position.y);
        yMax = std::max(yMax, vertex.position.y);
        zMin = std::min(zMin, vertex.position.z);
        zMax = std::max(zMax, vertex.position.z);
    }
}

void Mesh::recenter(glm::vec3 &center) {
    for (Vertex &vertex : vertices)
        vertex.position -= center;
}

void Mesh::render() {
    // TODO
}