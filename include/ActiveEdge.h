#ifndef ACTIVE_EDGE_H
#define ACTIVE_EDGE_H

#include "Edge.h"

class ActiveEdge {
private:
    int x, deltaX, deltaY, s;
    float z, dz;
    glm::vec3 p, dp, n, dn;

public:
    ActiveEdge(Edge &edge);
    ~ActiveEdge();
    int getX();
    float getZ();
    glm::vec3 getP();
    glm::vec3 getN();
    void update();
};

#endif