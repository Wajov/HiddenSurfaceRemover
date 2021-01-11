#ifndef ACTIVE_POLYGON_H
#define ACTIVE_POLYGON_H

#include <algorithm>
#include <map>

#include <glm/glm.hpp>

#include "Polygon.h"
#include "Edge.h"
#include "ActiveEdge.h"

class ActivePolygon {
private:
    int index;
    std::vector<Edge> edges;
    std::multimap<int, ActiveEdge> activeEdges;

public:
    ActivePolygon(Polygon &polygon);
    ~ActivePolygon();
    void check(int scanline);
    void update();
    void intersection(int &minX, int &maxX, float &z, float &dz, glm::vec3 &p, glm::vec3 &dp, glm::vec3 &n, glm::vec3 &dn);
};


#endif
