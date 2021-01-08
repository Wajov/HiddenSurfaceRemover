#ifndef Z_BUFFER_H
#define Z_BUFFER_H

#include <vector>

#include "Vertex.h"

class ZBuffer {
public:
    virtual void render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) = 0;
};

#endif