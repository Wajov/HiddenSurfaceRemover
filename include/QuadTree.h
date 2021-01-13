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
#include "ActivePolygon.h"
#include "Segment.h"
#include "ActiveSegment.h"
#include "Pixel.h"

class QuadTree {
private:
    int minX, maxX, minY, maxY;
    float maxZ;
    std::vector<QuadTree *> children;
    bool contain(Polygon &polygon);
    bool contain(Pixel &pixel);
    void update();
    void addPixels(std::vector<Pixel> &pixels, QImage &image);

public:
    QuadTree(int minX, int maxX, int minY, int maxY);
    ~QuadTree();
    void addPolygon(Polygon &polygon, QImage &image, ZBuffer *zBuffer);
};

#endif