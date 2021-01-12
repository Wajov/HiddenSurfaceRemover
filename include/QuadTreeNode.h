#ifndef QUAD_TREE_NODE_H
#define QUAD_TREE_NODE_H

#include <cfloat>
#include <vector>

class QuadTreeNode {
private:
    int minX, maxX, minY, maxY;
    float z;
    std::vector<QuadTreeNode *> children;

public:
    QuadTreeNode(int x, int y);
    ~QuadTreeNode();
};

#endif