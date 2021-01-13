#ifndef QUAD_TREE_NODE_H
#define QUAD_TREE_NODE_H

#include <algorithm>
#include <cfloat>
#include <climits>
#include <vector>

#include <QImage>

#include "ZBuffer.h"
#include "Polygon.h"
#include "ActiveEdge.h"

class QuadTree {
private:
    int minX, maxX, minY, maxY;
    float maxZ;
    std::vector<QuadTree *> children;
    bool contain(Polygon &polygon);

public:
    QuadTree(int minX, int maxX, int minY, int maxY);
    ~QuadTree();
    void addPolygon(Polygon &polygon, QImage &image, ZBuffer *zBuffer);
};

#endif