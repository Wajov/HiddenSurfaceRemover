#include "QuadTreeNode.h"

QuadTreeNode::QuadTreeNode(int x, int y) {
    minX = maxX = x;
    minY = maxY = y;
    z = FLT_MAX;
}

QuadTreeNode::~QuadTreeNode() {}