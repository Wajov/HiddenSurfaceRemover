#ifndef Z_BUFFER_H
#define Z_BUFFER_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Vertex.h"

class ZBuffer {
protected:
    int width, height;
    float lightPower;
    glm::vec3 ambientColor, diffuseColor, specularColor, cameraPosition, lightPosition;
    glm::mat4 model, MVP;
    glm::vec3 calculateColor(glm::vec3 &p, glm::vec3 &n);

public:
    ZBuffer(int width, int height);
    virtual void render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) = 0;
};

#endif