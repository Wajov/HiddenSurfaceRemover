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
public:
    ScanlineZBuffer(int width, int height);
    ~ScanlineZBuffer();
    QImage render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) override;
};

#endif