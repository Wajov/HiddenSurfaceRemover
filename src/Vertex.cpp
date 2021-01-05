#include "Vertex.h"

Vertex::Vertex(glm::vec3 &position, glm::vec3 &normal) {
    this->position = position;
    this->normal = normal;
}

Vertex::~Vertex() {}