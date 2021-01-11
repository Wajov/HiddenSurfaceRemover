#include "Polygon.h"

Polygon::Polygon(std::vector<Vertex> &vertices, glm::mat4 MVP, int width, int height) {
    for (int i = 0; i < vertices.size() - 1; i++) {
        edges.push_back(Edge(vertices[i], vertices[i + 1], MVP, width, height));
    }
    edges.push_back(Edge(*vertices.rbegin(), *vertices.begin(), MVP, width, height));

    int minY = INT_MAX, maxY = INT_MIN;
    for (Edge &edge : edges) {
        minY = std::min(minY, edge.getY());
        maxY = std::max(maxY, edge.getY() + edge.getDeltaY());
    }
    y = minY;
    deltaY = maxY - minY;
}

Polygon::~Polygon() {}

bool Polygon::operator <(Polygon &polygon) {
    if (y != polygon.y)
        return y < polygon.y;
    else
        return y + deltaY < polygon.y + polygon.deltaY;
}

std::vector<Edge> Polygon::getEdges() {
    return edges;
}

int Polygon::getY() {
    return y;
}

int Polygon::getDeltaY() {
    return deltaY;
}