#include "ActiveEdge.h"

ActiveEdge::ActiveEdge() {}

ActiveEdge::ActiveEdge(Edge &edge) {
    x = edge.getX();
    deltaX = edge.getDeltaX();
    y = edge.getY() + edge.getDeltaY();
    deltaY = edge.getDeltaY();
    z = edge.getZ();
    dz = edge.getDz();
    s = 0;
}

ActiveEdge::~ActiveEdge() {}

int ActiveEdge::getX() {
    return x;
}

int ActiveEdge::getY() {
    return y;
}

float ActiveEdge::getZ() {
    return z;
}

void ActiveEdge::update() {
    if (deltaX < 0)
        for (s += deltaX; -s >= deltaY; s += deltaY)
            x--;
    else
        for (s += deltaX; s >= deltaY; s -= deltaY)
            x++;
    z += dz;
}