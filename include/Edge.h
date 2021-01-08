#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"

class Edge {
private:
    int x, deltaX, y, deltaY;
    float z, dz;
    void coordinateToPixel(float coordinateX, float coordinateY, int &pixelX, int &pixelY);

public:
    Edge(Vertex &source, Vertex &target);
    ~Edge();
    bool operator <(Edge &edge);
    int getX();
    int getDeltaX();
    int getY();
    int getDeltaY();
    float getZ();
    float getDz();
};

#endif
