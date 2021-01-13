#ifndef NAIVE_HIERARCHICAL_Z_BUFFER_H
#define NAIVE_HIERARCHICAL_Z_BUFFER_H

#include <vector>

#include <QImage>
#include <QColor>

#include "Vertex.h"
#include "ZBuffer.h"
#include "QuadTree.h"
#include "Polygon.h"

class NaiveHierarchicalZBuffer : public ZBuffer {
public:
    NaiveHierarchicalZBuffer(int width, int height);
    ~NaiveHierarchicalZBuffer();
    QImage render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) override;
};

#endif