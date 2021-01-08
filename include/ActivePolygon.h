#ifndef ACTIVE_POLYGON_H
#define ACTIVE_POLYGON_H

#include <algorithm>
#include <map>

#include "Polygon.h"
#include "Edge.h"
#include "ActiveEdge.h"

class ActivePolygon {
private:
    std::vector<Edge> edges;
    std::map<int, ActiveEdge> activeEdges;

public:
    ActivePolygon(Polygon &polygon);
    ~ActivePolygon();
    void check(int scanline);
    void update();
    void intersection(int &minX, int &maxX, float &z, float &dz);
};


#endif
