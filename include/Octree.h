#ifndef OCTREE_H
#define OCTREE_H

#include <algorithm>
#include <vector>

#include "Polygon.h"

class Octree {
private:
    const int THRESHOLD = 1;
    int minX, maxX, minY, maxY;
    float minZ, maxZ, z;
    std::vector<Polygon> polygons;
    std::vector<Octree *> children;

public:
    Octree(int minX, int maxX, int minY, int maxY, float minZ, float maxZ, std::vector<Polygon> &polygons);
    ~Octree();
    int getMinX();
    int getMaxX();
    int getMinY();
    int getMaxY();
    float getZ();
    std::vector<Polygon> getPolygons();
    std::vector<Octree *> getChildren();
};

#endif