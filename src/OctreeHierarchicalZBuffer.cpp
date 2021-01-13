#include "OctreeHierarchicalZBuffer.h"

OctreeHierarchicalZBuffer::OctreeHierarchicalZBuffer(int width, int height) : ZBuffer(width, height) {}

OctreeHierarchicalZBuffer::~OctreeHierarchicalZBuffer() {}

QImage OctreeHierarchicalZBuffer::render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) {
    std::vector<Polygon> polygons;
    for (auto iter = indices.begin(); iter != indices.end(); ) {
        std::vector<Vertex> polygonVertices;
        for (int i = 0; i < 3; i++)
            polygonVertices.push_back(vertices[*(iter++)]);
        Polygon polygon(polygonVertices, MVP, width, height);
        if (polygon.getDeltaY() > 0)
            polygons.push_back(polygon);
    }

    
}