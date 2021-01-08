#include "ActiveEdge.h"

ActiveEdge::ActiveEdge(Edge &edge) {
    x = edge.getX();
    deltaX = edge.getDeltaX();
    y = 0;
    deltaY = edge.getDeltaY();
    z = edge.getZ();
    dz = edge.getDz();
}

ActiveEdge::~ActiveEdge() {}

int ActiveEdge::getX() {
    return x;
}

float ActiveEdge::getZ() {
    return z;
}

void ActiveEdge::update() {
    y++;
    x = x0 + deltaX / deltaY * y;
    z += dz;
}