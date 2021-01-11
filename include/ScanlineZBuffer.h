#ifndef SCANLINE_Z_BUFFER_H
#define SCANLINE_Z_BUFFER_H

#include <algorithm>
#include <cfloat>
#include <cstring>
#include <vector>
#include <map>

#include <QImage>
#include <QColor>

#include "Vertex.h"
#include "Polygon.h"
#include "ActivePolygon.h"
#include "ZBuffer.h"

class ScanlineZBuffer : public ZBuffer {
private:
    std::vector<Polygon> polygons;
    std::multimap<int, ActivePolygon> activePolygons;

public:
    ScanlineZBuffer(int width, int height);
    QImage render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) override;
};

#endif