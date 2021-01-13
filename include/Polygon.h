#ifndef POLYGON_H
#define POLYGON_H

#include <climits>
#include <vector>

#include <glm/glm.hpp>

#include "Vertex.h"
#include "Edge.h"

class Polygon {
private:
    int x, deltaX, y, deltaY;
    float z;
    std::vector<Edge> edges;

public:
    Polygon(std::vector<Vertex> &vertices, glm::mat4 MVP, int width, int height);
    ~Polygon();
    bool operator <(Polygon &polygon);
    int getX();
    int getDeltaX();
    int getY();
    int getDeltaY();
    float getZ();
    std::vector<Edge> getEdges();
};

#endif