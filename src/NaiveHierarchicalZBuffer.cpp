#include "NaiveHierarchicalZBuffer.h"

NaiveHierarchicalZBuffer::NaiveHierarchicalZBuffer(int width, int height) : ZBuffer(width, height) {}

NaiveHierarchicalZBuffer::~NaiveHierarchicalZBuffer() {}

QuadTreeNode *NaiveHierarchicalZBuffer::buildQuadTree(int minX, int maxX, int minY, int maxY) {
    if (minX == maxX && minY == maxY)
        return new QuadTreeNode(minX, minY);
    std::vector<QuadTreeNode *> children;
    int middleX = (minX + maxX) / 2, middleY = (minY + maxY) / 2;
    
}

QImage NaiveHierarchicalZBuffer::render(std::vector <Vertex> &vertices, std::vector<unsigned int> &indices) {
    root = buildQuadTree(0, width - 1, 0, height - 1);
}