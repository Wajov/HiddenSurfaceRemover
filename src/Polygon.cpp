#include "Polygon.h"

Polygon::Polygon(std::vector<Vertex> &vertices) {
    for (int i = 0; i < vertices.size() - 1; i++) {
        edges.push_back(Edge(vertices[i], vertices[i + 1]));
    }
    edges.push_back(Edge(*vertices.rbegin(), *vertices.begin()));

    int minY = INT_MAX, maxY = INT_MIN;
    for (Edge &edge : edges) {
        minY = std::min(minY, edge.getY());
        maxY = std::min(maxY, edge.getY() + edge.getDeltaY());
    }
    y = minY;
    deltaY = maxY - minY;
}

Polygon::~Polygon() {}

bool Polygon::operator <(Polygon &polygon) {
    return y < polygon.y || (y == polygon.y && y + deltaY < polygon.y + polygon.deltaY);
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