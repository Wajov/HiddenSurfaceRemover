#ifndef Z_BUFFER_H
#define Z_BUFFER_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <QImage>

#include "Vertex.h"
#include "Pixel.h"
#include "Polygon.h"
#include "ActivePolygon.h"
#include "Segment.h"
#include "ActiveSegment.h"

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
    virtual ~ZBuffer();
    float getFactor();
    void setFactor(float factor);
    glm::mat4 getRotate();
    void setRotate(glm::mat4 &rotate);
    std::vector<Pixel> calculatePixels(Polygon &polygon, int minX, int maxX, int minY, int maxY);
    virtual QImage render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) = 0;
};

#endif