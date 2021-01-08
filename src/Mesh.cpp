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
        glm::vec3 position = vertex.getPosition();
        xMin = std::min(xMin, position.x);
        xMax = std::max(xMax, position.x);
        yMin = std::min(yMin, position.y);
        yMax = std::max(yMax, position.y);
        zMin = std::min(zMin, position.z);
        zMax = std::max(zMax, position.z);
    }
}

void Mesh::recenter(glm::vec3 &center) {
    for (Vertex &vertex : vertices) {
        glm::vec3 position = vertex.getPosition() - center;
        vertex.setPosition(position);
    }
}

void Mesh::render(ZBuffer *zBuffer) {
    zBuffer->render(vertices, indices);
}