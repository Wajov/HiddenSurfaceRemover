#ifndef Z_BUFFER_H
#define Z_BUFFER_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <QImage>

#include "Vertex.h"

class ZBuffer {
protected:
    int width, height;
    float factor, lightPower;
    glm::vec3 ambientColor, diffuseColor, specularColor, cameraPosition, lightPosition;
    glm::mat4 rotate, MVP;
    void calculateMVP();
    glm::vec3 calculateColor(glm::vec3 &p, glm::vec3 &n);

public:
    ZBuffer(int width, int height);
    ~ZBuffer();
    float getFactor();
    void setFactor(float factor);
    glm::mat4 getRotate();
    void setRotate(glm::mat4 &rotate);
    virtual QImage render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) = 0;
};

#endif