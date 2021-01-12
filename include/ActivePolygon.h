#ifndef ACTIVE_POLYGON_H
#define ACTIVE_POLYGON_H

#include <algorithm>
#include <climits>
#include <vector>
#include <map>

#include <glm/glm.hpp>

#include "Polygon.h"
#include "Edge.h"
#include "Segment.h"
#include "ActiveEdge.h"

class ActivePolygon {
private:
    int index, leftY, rightY;
    std::vector<Edge> edges;
    ActiveEdge leftEdge, rightEdge;

public:
    ActivePolygon(Polygon &polygon);
    ~ActivePolygon();
    void check(int scanline);
    void update();
    Segment segment();
};

#endif
