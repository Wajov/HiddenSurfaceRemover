#include "ActivePolygon.h"

ActivePolygon::ActivePolygon(Polygon &polygon) {
    edges = polygon.getEdges();
    std::sort(edges.begin(), edges.end());
    index = 0;
    for (int i = 0; i < 2; i++, index++)
        activeEdges.insert(std::make_pair(edges[index].getY() + edges[index].getDeltaY(), ActiveEdge(edges[index])));
}

ActivePolygon::~ActivePolygon() {}

void ActivePolygon::check(int scanline) {
    while (!activeEdges.empty() && activeEdges.begin()->first == scanline) {
        activeEdges.erase(activeEdges.begin());
        if (index < edges.size()) {
            activeEdges.insert(std::make_pair(edges[index].getY() + edges[index].getDeltaY(), ActiveEdge(edges[index])));
            index++;
        }
    }
}

void ActivePolygon::update() {
    for (std::pair<const int, ActiveEdge> &pair : activeEdges)
        pair.second.update();
}

void ActivePolygon::intersection(int &minX, int &maxX, float &z, float &dz, glm::vec3 &p, glm::vec3 &dp, glm::vec3 &n, glm::vec3 &dn) {
    if (activeEdges.size() < 2) {
        minX = 0;
        maxX = -1;
    } else {
        ActiveEdge left = activeEdges.begin()->second;
        ActiveEdge right = activeEdges.rbegin()->second;
        if (left.getX() > right.getX())
            std::swap(left, right);
        minX = left.getX();
        maxX = right.getX();
        float deltaX = maxX - minX;
        z = left.getZ();
        dz = (right.getZ() - left.getZ()) / deltaX;
        p = left.getP();
        dp = (right.getP() - left.getP()) / deltaX;
        n = left.getN();
        dn = (right.getN() - left.getN()) / deltaX;
    }
}