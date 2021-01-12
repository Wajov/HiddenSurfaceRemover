#include "ActivePolygon.h"

ActivePolygon::ActivePolygon(Polygon &polygon) {
    edges = polygon.getEdges();
    std::sort(edges.begin(), edges.end());
    index = 0;
    leftY = edges[index].getY() + edges[index].getDeltaY();
    leftEdge = ActiveEdge(edges[index++]);
    rightY = edges[index].getY() + edges[index].getDeltaY();
    rightEdge = ActiveEdge(edges[index++]);
}

ActivePolygon::~ActivePolygon() {}

void ActivePolygon::check(int scanline) {
    while (leftY == scanline || rightY == scanline) {
        if (leftY == scanline) {
            if (index < edges.size()) {
                leftY = edges[index].getY() + edges[index].getDeltaY();
                leftEdge = ActiveEdge(edges[index++]);
            } else
                leftY = INT_MIN;
        }
        if (rightY == scanline) {
            if (index < edges.size()) {
                rightY = edges[index].getY() + edges[index].getDeltaY();
                rightEdge = ActiveEdge(edges[index++]);
            } else
                rightY = INT_MIN;
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
    if (leftY != INT_MAX && rightY != INT_MAX) {
        int deltaX = rightEdge.getX() - leftEdge.getX();
        float dz = (rightEdge.getZ() - leftEdge.getZ()) / deltaX;
        glm::vec3 p = leftEdge.getP();
        glm::vec3 dp = (rightEdge.getP() - leftEdge.getP()) / (float)deltaX;
        glm::vec3 n = leftEdge.getN();
        glm::vec3 dn = (rightEdge.getN() - leftEdge.getN()) / (float)deltaX;
        return Segment(leftEdge.getX(), deltaX, leftEdge.getZ(), dz, p, dp, n, dn);
    } else {
        glm::vec3 zero(0.0f);
        return Segment(0, -1, 0, 0, zero, zero, zero, zero);
    }
}