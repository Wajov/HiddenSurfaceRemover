#ifndef ACTIVE_EDGE_H
#define ACTIVE_EDGE_H

#include "Edge.h"

class ActiveEdge {
private:
    int x, deltaX, deltaY, s;
    float z, dz;

public:
    ActiveEdge(Edge &edge);
    ~ActiveEdge();
    int getX();
    float getZ();
    void update();
};

#endif