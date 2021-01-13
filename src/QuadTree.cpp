#include "QuadTree.h"

QuadTree::QuadTree(int minX, int maxX, int minY, int maxY) {
    this->minX = minX;
    this->maxX = maxX;
    this->minY = minY;
    this->maxY = maxY;
    maxZ = FLT_MAX;
    if (minX != maxX || minY != maxY) {
        int middleX = (minX + maxX) / 2, middleY = (minY + maxY) / 2;
        children.push_back(new QuadTree(minX, middleX, minY, middleY));
        if (middleX + 1 <= maxX)
            children.push_back(new QuadTree(middleX + 1, maxX, minY, middleY));
        if (middleY + 1 <= maxY)
            children.push_back(new QuadTree(minX, middleX, middleY + 1, maxY));
        if (middleX + 1 <= maxX && middleY + 1 <= maxY)
            children.push_back(new QuadTree(middleX + 1, maxX, middleY + 1, maxY));
    }
}

QuadTree::~QuadTree() {
    for (QuadTree *child : children)
        delete child;
}

bool QuadTree::contain(Polygon &polygon) {
    return minX <= polygon.getX() && maxX >= polygon.getX() + polygon.getDeltaX() && minY <= polygon.getY() && maxY >= polygon.getY() + polygon.getDeltaY();
}

void QuadTree::addPolygon(Polygon &polygon, QImage &image, ZBuffer *zBuffer) {
    if (maxZ <= polygon.getZ())
        return;

    bool flag = true;
    for (QuadTree *child : children)
        if (child->contain(polygon)) {
            child->addPolygon(polygon, image, zBuffer);
            flag = false;
        }

    if (flag) {

    }
}