#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Vertex.h"
#include "Texture.h"

class Mesh {
private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

public:
    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
    ~Mesh();
    void coordinateRange(float &xMin, float &xMax, float &yMin, float &yMax, float &zMin, float &zMax);
    void recenter(glm::vec3 &center);
    void render();
};

#endif