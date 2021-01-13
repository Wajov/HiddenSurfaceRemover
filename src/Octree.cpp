#include "Octree.h"

Octree::Octree(int minX, int maxX, int minY, int maxY, float minZ, float maxZ, std::vector<Polygon> &polygons) {
    this->minX = minX;
    this->maxX = maxX;
    this->minY = minY;
    this->maxY = maxY;
    this->minZ = minZ;
    this->maxZ = maxZ;
    if (polygons.size() <= THRESHOLD) {
        z = minZ;
        this->polygons = polygons;
    } else {
        int middleX = (minX + maxX) / 2, middleY = (minY + maxY) / 2;
        float middleZ = (minZ + maxZ) / 2;
        std::vector<std::vector<Polygon>> childPolygons(8);
        for (Polygon &polygon : polygons)
            if (polygon.getX() + polygon.getDeltaX() <= middleX && polygon.getY() + polygon.getDeltaY() <= middleY && polygon.getZ() + polygon.getDeltaZ() <= middleZ)
                childPolygons[0].push_back(polygon);
            else if (polygon.getX() + polygon.getDeltaX() <= middleX && polygon.getY() + polygon.getDeltaY() <= middleY && polygon.getZ() > middleZ)
                childPolygons[1].push_back(polygon);
            else if (polygon.getX() + polygon.getDeltaX() <= middleX && polygon.getY() > middleY && polygon.getZ() + polygon.getDeltaZ() <= middleZ)
                childPolygons[2].push_back(polygon);
            else if (polygon.getX() + polygon.getDeltaX() <= middleX && polygon.getY() > middleY && polygon.getZ() > middleZ)
                childPolygons[3].push_back(polygon);
            else if (polygon.getX() > middleX && polygon.getY() + polygon.getDeltaY() <= middleY && polygon.getZ() + polygon.getDeltaZ() <= middleZ)
                childPolygons[4].push_back(polygon);
            else if (polygon.getX() > middleX && polygon.getY() + polygon.getDeltaY() <= middleY && polygon.getZ() > middleZ)
                childPolygons[5].push_back(polygon);
            else if (polygon.getX() > middleX && polygon.getY() > middleY && polygon.getZ() + polygon.getDeltaZ() <= middleZ)
                childPolygons[6].push_back(polygon);
            else if (polygon.getX() > middleX && polygon.getY() > middleY && polygon.getZ() > middleZ)
                childPolygons[7].push_back(polygon);
            else
                this->polygons.push_back(polygon);
        children.push_back(new Octree(minX, middleX, minY, middleY, minZ, middleZ, childPolygons[0]));
        children.push_back(new Octree(minX, middleX, minY, middleY, middleZ, maxZ, childPolygons[1]));
        children.push_back(new Octree(minX, middleX, middleY + 1, maxY, minZ, middleZ, childPolygons[2]));
        children.push_back(new Octree(minX, middleX, middleY + 1, maxY, middleZ, maxZ, childPolygons[3]));
        children.push_back(new Octree(middleX + 1, maxX, minY, middleY, minZ, middleZ, childPolygons[4]));
        children.push_back(new Octree(middleX + 1, maxX, minY, middleY, middleZ, maxZ, childPolygons[5]));
        children.push_back(new Octree(middleX + 1, maxX, middleY + 1, maxY, minZ, middleZ, childPolygons[6]));
        children.push_back(new Octree(middleX + 1, maxX, middleY + 1, maxY, middleZ, maxZ, childPolygons[7]));
        for (Octree *child : children)
            z = std::min(z, child->z);
    }
}

Octree::~Octree() {
    for (Octree *child : children)
        delete child;
}

int Octree::getMinX() {
    return minX;
}

int Octree::getMaxX() {
    return maxX;
}

int Octree::getMinY() {
    return minY;
}

int Octree::getMaxY() {
    return maxY;
}

float Octree::getZ() {
    return z;
}

std::vector<Polygon> Octree::getPolygons() {
    return polygons;
}

std::vector<Octree *> Octree::getChildren() {
    return children;
}