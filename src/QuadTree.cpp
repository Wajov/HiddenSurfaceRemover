#include "QuadTree.h"

QuadTree::QuadTree(int minX, int maxX, int minY, int maxY) {
    this->minX = minX;
    this->maxX = maxX;
    this->minY = minY;
    this->maxY = maxY;
    z = FLT_MAX;
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

bool QuadTree::contain(Pixel &pixel) {
    return minX <= pixel.getX() && maxX >= pixel.getX() && minY <= pixel.getY() && maxY >= pixel.getY();
}

bool QuadTree::contain(Polygon &polygon) {
    return minX <= polygon.getX() && maxX >= polygon.getX() + polygon.getDeltaX() && minY <= polygon.getY() && maxY >= polygon.getY() + polygon.getDeltaY();
}

bool QuadTree::contain(Octree *octree) {
    return minX <= octree->getMinX() && maxX >= octree->getMaxX() && minY <= octree->getMinY() && maxY >= octree->getMaxY();
}

void QuadTree::update() {
    z = -FLT_MAX;
    for (QuadTree *child : children)
        z = std::max(z, child->z);
}

void QuadTree::addPixels(std::vector<Pixel> &pixels, QImage &image) {
    float minZ = FLT_MAX;
    for (Pixel &pixel : pixels)
        minZ = std::min(minZ, pixel.getZ());
    if (z <= minZ)
        return;

    if (minX == maxX && minY == maxY) {
        for (Pixel &pixel : pixels)
            if (pixel.getZ() < z) {
                z = pixel.getZ();
                image.setPixel(pixel.getX(), pixel.getY(), pixel.getColor().rgb());
            }
    } else {
        std::vector<std::vector<Pixel>> childPixels(children.size());
        for (Pixel &pixel : pixels)
            for (int i = 0; i < children.size(); i++)
                if (children[i]->contain(pixel)) {
                    childPixels[i].push_back(pixel);
                    break;
                }
        for (int i = 0; i < children.size(); i++)
            if (!childPixels[i].empty())
                children[i]->addPixels(childPixels[i], image);
        update();
    }
}

void QuadTree::addPolygon(Polygon &polygon, QImage &image, ZBuffer *zBuffer) {
    if (z <= polygon.getZ())
        return;

    bool flag = true;
    for (QuadTree *child : children)
        if (child->contain(polygon)) {
            child->addPolygon(polygon, image, zBuffer);
            flag = false;
            update();
            break;
        }

    if (flag) {
        std::vector<Pixel> pixels = zBuffer->calculatePixels(polygon, minX, maxX, minY, maxY);
        addPixels(pixels, image);
    }
}

void QuadTree::addOctree(Octree *octree, QImage &image, ZBuffer *zBuffer) {
    if (z <= octree->getZ())
        return;

    std::vector<Polygon> polygons = octree->getPolygons();
    for (Polygon &polygon : polygons) {
        std::vector<Pixel> pixels = zBuffer->calculatePixels(polygon, minX, maxX, minY, maxY);
        addPixels(pixels, image);
    }

    std::vector<Octree *> octreeChildren = octree->getChildren();
    for (Octree *octreeChild : octreeChildren)
        for (QuadTree *child : children)
            if (child->contain(octreeChild))
                child->addOctree(octreeChild, image, zBuffer);
    update();
}