#ifndef POLYGON_H
#define POLYGON_H

#include <climits>
#include <cfloat>
#include <vector>

#include <QMatrix4x4>

#include "Vertex.h"
#include "Edge.h"

class Polygon {
private:
    int x, deltaX, y, deltaY;
    float z, deltaZ;
    std::vector<Edge> edges;

public:
    Polygon(std::vector<Vertex> &vertices, QMatrix4x4 &MVP, int width, int height);
    ~Polygon();
    bool operator <(Polygon &polygon);
    int getX();
    int getDeltaX();
    int getY();
    int getDeltaY();
    float getZ();
    float getDeltaZ();
    std::vector<Edge> getEdges();
};

#endif