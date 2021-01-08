#ifndef SCANLINE_Z_BUFFER_H
#define SCANLINE_Z_BUFFER_H

#include <vector>
#include <set>

#include "Vertex.h"
#include "Edge.h"
#include "ZBuffer.h"

class ScanlineZBuffer : public ZBuffer {
private:
    std::set<Edge> edges, activeEdges;

public:
    void render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) override;
};

#endif