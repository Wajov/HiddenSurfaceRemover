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

bool QuadTree::contain(Pixel &pixel) {
    return minX <= pixel.getX() && maxX >= pixel.getX() && minY <= pixel.getY() && maxY >= pixel.getY();
}

void QuadTree::update() {
    maxZ = -FLT_MAX;
    for (QuadTree *child : children)
        maxZ = std::max(maxZ, child->maxZ);
}

void QuadTree::addPixels(std::vector<Pixel> &pixels, QImage &image) {
    float minZ = FLT_MAX;
    for (Pixel &pixel : pixels)
        minZ = std::min(minZ, pixel.getZ());
    if (maxZ <= minZ)
        return;

    if (minX == maxX && minY == maxY) {
        for (Pixel &pixel : pixels)
            if (pixel.getZ() < maxZ) {
                maxZ = pixel.getZ();
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
    if (maxZ <= polygon.getZ())
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
        std::vector<Pixel> pixels;
        ActivePolygon activePolygon(polygon);
        for (int scanlineY = polygon.getY(); scanlineY <= polygon.getY() + polygon.getDeltaY() && scanlineY <= maxY; scanlineY++) {
            activePolygon.check(scanlineY);

            if (scanlineY >= minY) {
                Segment segment = activePolygon.segment();
                ActiveSegment activeSegment(segment);

                for (int scanlineX = segment.getX(); scanlineX <= segment.getX() + segment.getDeltaX() && scanlineX <= maxX; scanlineX++) {
                    if (scanlineX >= minX) {
                        float z = activeSegment.getZ();
                        glm::vec3 p = activeSegment.getP(), n = activeSegment.getN();
                        glm::vec3 colorTemp = zBuffer->calculateColor(p, n);
                        QColor color((int)(colorTemp.x * 255), (int)(colorTemp.y * 255), (int)(colorTemp.z * 255));
                        pixels.push_back(Pixel(scanlineX, scanlineY, z, color));
                    }
                    activeSegment.update();
                }
            }
            activePolygon.update();
        }
        addPixels(pixels, image);
    }
}