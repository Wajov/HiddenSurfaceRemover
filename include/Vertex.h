#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

class Vertex {
private:
    glm::vec3 position, normal;

public:
    Vertex(glm::vec3 &position, glm::vec3 &normal);
    ~Vertex();
};

#endif