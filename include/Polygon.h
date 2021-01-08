#ifndef POLYGON_H
#define POLYGON_H

#include <climits>
#include <vector>

#include "Vertex.h"
#include "Edge.h"

class Polygon {
private:
    std::vector<Edge> edges;
    int y, deltaY;

public:
    Polygon(std::vector<Vertex> &vertices);
    ~Polygon();
    bool operator <(Polygon &polygon);
    std::vector<Edge> getEdges();
    int getY();
    int getDeltaY();
};

#endif