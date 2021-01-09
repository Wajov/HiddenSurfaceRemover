#ifndef ACTIVE_EDGE_H
#define ACTIVE_EDGE_H

#include "Edge.h"

class ActiveEdge {
private:
    int x, deltaX, y, deltaY, s;
    float z, dz;

public:
    ActiveEdge();
    ActiveEdge(Edge &edge);
    ~ActiveEdge();
    int getX();
    int getY();
    float getZ();
    void update();
};

#endif