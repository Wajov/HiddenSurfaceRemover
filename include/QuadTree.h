#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include <algorithm>
#include <cfloat>
#include <climits>
#include <vector>

#include <glm/glm.hpp>
#include <QImage>
#include <QColor>

#include "ZBuffer.h"
#include "Polygon.h"
#include "Octree.h"
#include "Pixel.h"

class QuadTree {
private:
    int minX, maxX, minY, maxY;
    float z;
    std::vector<QuadTree *> children;
    bool contain(Pixel &pixel);
    bool contain(Polygon &polygon);
    bool contain(Octree *octree);
    void update();
    void addPixels(std::vector<Pixel> &pixels, QImage &image);

public:
    QuadTree(int minX, int maxX, int minY, int maxY);
    ~QuadTree();
    void addPolygon(Polygon &polygon, QImage &image, ZBuffer *zBuffer);
    void addOctree(Octree *octree, QImage &image, ZBuffer *zBuffer);
};

#endif