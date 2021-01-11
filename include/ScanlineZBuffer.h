#ifndef SCANLINE_Z_BUFFER_H
#define SCANLINE_Z_BUFFER_H

#include <algorithm>
#include <vector>
#include <map>

#include <stb/stb_image_write.h>

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
    void render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) override;
};

#endif