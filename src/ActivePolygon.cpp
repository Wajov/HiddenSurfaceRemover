#include "ActivePolygon.h"

ActivePolygon::ActivePolygon(Polygon &polygon) {
    edges = polygon.getEdges();
    std::sort(edges.begin(), edges.end());
    auto iter = edges.begin();
    for (int i = 0; i < 2; i++, iter++)
        activeEdges.insert(std::make_pair(iter->getY() + iter->getDeltaY(), ActiveEdge(*iter)));
}

ActivePolygon::~ActivePolygon() {}

void ActivePolygon::check(int scanline) {
    while (activeEdges.begin()->first == scanline) {
        for (Edge &edge : edges)
            if (activeEdges.begin()->second.getX() == edge.getX()) {
                activeEdges.erase(activeEdges.begin());
                activeEdges.insert(std::make_pair(edge.getY() + edge.getDeltaY(), ActiveEdge(edge)));
            }
    }
}

void ActivePolygon::update() {
    for (std::pair<const int, ActiveEdge> &pair : activeEdges)
        pair.second.update();
}

void ActivePolygon::intersection(int &minX, int &maxX, float &z, float &dz) {
    ActiveEdge left = activeEdges.begin()->second, right = activeEdges.rbegin()->second;
    if (left.getX() > right.getX())
        std::swap(left, right);
    minX = left.getX();
    maxX = right.getX();
    z = left.getZ();
    dz = (right.getZ() - left.getZ()) / (maxX - minX);
}