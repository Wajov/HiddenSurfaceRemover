#include "Vertex.h"

Vertex::Vertex(glm::vec3 &position, glm::vec3 &normal) {
    this->position = position;
    this->normal = normal;
}

Vertex::~Vertex() {}

glm::vec3 Vertex::getPosition() {
    return position;
}

void Vertex::setPosition(glm::vec3 &position) {
    this->position = position;
}

glm::vec3 Vertex::getNormal() {
    return normal;
}