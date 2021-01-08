#include "ActiveEdge.h"

ActiveEdge::ActiveEdge(Edge &edge) {
    x = edge.getX();
    deltaX = edge.getDeltaX();
    deltaY = edge.getDeltaY();
    z = edge.getZ();
    dz = edge.getDz();
    s = 0;
}

ActiveEdge::~ActiveEdge() {}

int ActiveEdge::getX() {
    return x;
}

float ActiveEdge::getZ() {
    return z;
}

void ActiveEdge::update() {
    s += deltaX;
    for (s += deltaX; s >= deltaY; s -= deltaY)
        x++;
    z += dz;
}