#ifndef SCANLINE_Z_BUFFER_H
#define SCANLINE_Z_BUFFER_H

#define STB_IMAGE_WRITE_IMPLEMENTATION

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
    glm::vec3 calculateColor();

public:
    void render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) override;
};

#endif