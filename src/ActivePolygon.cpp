#include "ActivePolygon.h"

ActivePolygon::ActivePolygon(Polygon &polygon) {
    std::vector<Edge> edgesTemp = polygon.getEdges();
    for (Edge &edge : edgesTemp)
        if (edge.getDeltaY() > 0)
            edges.push_back(edge);
    std::sort(edges.begin(), edges.end());
    index = 0;
    leftY = edges[index].getY() + edges[index].getDeltaY();
    leftEdge = ActiveEdge(edges[index++]);
    rightY = edges[index].getY() + edges[index].getDeltaY();
    rightEdge = ActiveEdge(edges[index++]);
}

ActivePolygon::~ActivePolygon() {}

void ActivePolygon::check(int scanline) {
    while (index < edges.size() && (leftY == scanline || rightY == scanline)) {
        if (leftY == scanline) {
            leftY = edges[index].getY() + edges[index].getDeltaY();
            leftEdge = ActiveEdge(edges[index++]);
        }
        if (rightY == scanline) {
            rightY = edges[index].getY() + edges[index].getDeltaY();
            rightEdge = ActiveEdge(edges[index++]);
        }
    }

    if (leftEdge.getX() > rightEdge.getX()) {
        std::swap(leftY, rightY);
        std::swap(leftEdge, rightEdge);
    }
}

void ActivePolygon::update() {
    leftEdge.update();
    rightEdge.update();
}

Segment ActivePolygon::segment() {
    int deltaX = rightEdge.getX() - leftEdge.getX();
    float dz = (rightEdge.getZ() - leftEdge.getZ()) / deltaX;
    QVector3D p = leftEdge.getP();
    QVector3D dp = (rightEdge.getP() - leftEdge.getP()) / (float)deltaX;
    QVector3D n = leftEdge.getN();
    QVector3D dn = (rightEdge.getN() - leftEdge.getN()) / (float)deltaX;
    return Segment(leftEdge.getX(), deltaX, leftEdge.getZ(), dz, p, dp, n, dn);
}