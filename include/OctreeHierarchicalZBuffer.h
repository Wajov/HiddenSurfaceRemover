#ifndef OCTREE_HIERARCHICAL_Z_BUFFER_H
#define OCTREE_HIERARCHICAL_Z_BUFFER_H

#include <algorithm>
#include <cfloat>
#include <vector>

#include <QImage>
#include <QColor>

#include "Vertex.h"
#include "ZBuffer.h"
#include "QuadTree.h"
#include "Octree.h"
#include "Polygon.h"

class OctreeHierarchicalZBuffer : public ZBuffer{
public:
    OctreeHierarchicalZBuffer(int width, int height);
    ~OctreeHierarchicalZBuffer();
    QImage render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) override;
};

#endif