#include "ActiveEdge.h"

ActiveEdge::ActiveEdge() {}

ActiveEdge::ActiveEdge(Edge &edge) {
    x = edge.getX();
    deltaX = edge.getDeltaX();
    deltaY = edge.getDeltaY();
    z = edge.getZ();
    dz = edge.getDz();
    p = edge.getP();
    dp = edge.getDp();
    n = edge.getN();
    dn = edge.getDn();
    s = 0;
}

ActiveEdge::~ActiveEdge() {}

int ActiveEdge::getX() {
    return x;
}

float ActiveEdge::getZ() {
    return z;
}

QVector3D ActiveEdge::getP() {
    return p;
}

QVector3D ActiveEdge::getN() {
    return n;
}

void ActiveEdge::update() {
    if (deltaX < 0)
        for (s += deltaX; -s >= deltaY; s += deltaY)
            x--;
    else
        for (s += deltaX; s >= deltaY; s -= deltaY)
            x++;
    z += dz;
    p += dp;
    n += dn;
}