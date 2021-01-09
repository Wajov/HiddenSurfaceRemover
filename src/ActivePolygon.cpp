#include "ActivePolygon.h"

ActivePolygon::ActivePolygon(Polygon &polygon) {
    edges = polygon.getEdges();
    std::sort(edges.begin(), edges.end());
    iter = edges.begin();
    leftEdge = ActiveEdge(*(iter++));
    rightEdge = ActiveEdge(*(iter++));
}

ActivePolygon::~ActivePolygon() {}

void ActivePolygon::check(int scanline) {
    if (leftEdge.getY() == scanline && iter != edges.end())
        leftEdge = ActiveEdge(*(iter++));
    if (rightEdge.getY() == scanline && iter != edges.end())
        rightEdge = ActiveEdge(*(iter++));
}

void ActivePolygon::update() {
    leftEdge.update();
    rightEdge.update();
}

void ActivePolygon::intersection(int &minX, int &maxX, float &z, float &dz) {
    minX = leftEdge.getX();
    maxX = rightEdge.getX();
    z = leftEdge.getZ();
    dz = (rightEdge.getZ() - leftEdge.getZ()) / (maxX - minX);
}