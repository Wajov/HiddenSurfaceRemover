#include "OctreeHierarchicalZBuffer.h"

OctreeHierarchicalZBuffer::OctreeHierarchicalZBuffer(int width, int height) : ZBuffer(width, height) {}

OctreeHierarchicalZBuffer::~OctreeHierarchicalZBuffer() {}

QImage OctreeHierarchicalZBuffer::render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) {
    float minZ = FLT_MAX, maxZ = -FLT_MAX;
    std::vector<Polygon> polygons;
    for (auto iter = indices.begin(); iter != indices.end(); ) {
        std::vector<Vertex> polygonVertices;
        for (int i = 0; i < 3; i++)
            polygonVertices.push_back(vertices[*(iter++)]);
        Polygon polygon(polygonVertices, MVP, width, height);
        if (polygon.getDeltaX() > 0 && polygon.getDeltaY() > 0) {
            polygons.push_back(polygon);
            minZ = std::min(minZ, polygon.getZ());
            maxZ = std::max(maxZ, polygon.getZ() + polygon.getDeltaZ());
        }
    }

    QuadTree *rootQuadTree = new QuadTree(0, width - 1, 0, height - 1);
    Octree *rootOctree = new Octree(0, width - 1, 0, height - 1, minZ, maxZ, polygons);
    QImage ans(width, height, QImage::Format_RGB32);
    ans.fill(QColor(0, 0, 0));
    rootQuadTree->addOctree(rootOctree, ans, this);
    delete rootQuadTree;
    delete rootOctree;

    return ans;
}