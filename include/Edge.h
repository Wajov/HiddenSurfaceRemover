#ifndef EDGE_H
#define EDGE_H

#include <algorithm>

#include <glm/glm.hpp>

#include "Vertex.h"

class Edge {
private:
    int x, deltaX, y, deltaY;
    float z, dz;
    glm::vec3 p, dp, n, dn;
    void coordinateToPixel(float coordinateX, float coordinateY, int &pixelX, int &pixelY, int width, int height);

public:
    Edge(Vertex &source, Vertex &target, glm::mat4 MVP, int width, int height);
    ~Edge();
    bool operator <(Edge &edge);
    int getX();
    int getDeltaX();
    int getY();
    int getDeltaY();
    float getZ();
    float getDz();
    glm::vec3 getP();
    glm::vec3 getDp();
    glm::vec3 getN();
    glm::vec3 getDn();
};

#endif
