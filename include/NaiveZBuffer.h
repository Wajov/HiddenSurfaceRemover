#ifndef NAIVE_Z_BUFFER_H
#define NAIVE_Z_BUFFER_H

#include <cfloat>
#include <vector>

#include <QImage>

#include "Vertex.h"
#include "ZBuffer.h"

class NaiveZBuffer : public ZBuffer {
public:
    NaiveZBuffer(int width, int height);
    ~NaiveZBuffer() override;
    QImage render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) override;
};

#endif