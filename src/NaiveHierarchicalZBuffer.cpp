#include "NaiveHierarchicalZBuffer.h"

NaiveHierarchicalZBuffer::NaiveHierarchicalZBuffer(int width, int height) : ZBuffer(width, height) {}

NaiveHierarchicalZBuffer::~NaiveHierarchicalZBuffer() {}

QImage NaiveHierarchicalZBuffer::render(std::vector <Vertex> &vertices, std::vector<unsigned int> &indices) {
    QuadTree *root = new QuadTree(0, width - 1, 0, height - 1);
    QImage ans(width, height, QImage::Format_RGB32);
    ans.fill(QColor(0, 0, 0));
    for (auto iter = indices.begin(); iter != indices.end(); ) {
        std::vector<Vertex> polygonVertices;
        for (int i = 0; i < 3; i++)
            polygonVertices.push_back(vertices[*(iter++)]);
        Polygon polygon(polygonVertices, MVP, width, height);
        if (polygon.getDeltaX() > 0 && polygon.getDeltaY() > 0)
            root->addPolygon(polygon, ans, this);
    }
    delete root;

    return ans;
}