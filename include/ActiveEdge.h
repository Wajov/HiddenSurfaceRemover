#ifndef ACTIVE_EDGE_H
#define ACTIVE_EDGE_H

#include <QVector3D>

#include "Edge.h"

class ActiveEdge {
private:
    int x, deltaX, deltaY, s;
    float z, dz;
    QVector3D p, dp, n, dn;

public:
    ActiveEdge();
    ActiveEdge(Edge &edge);
    ~ActiveEdge();
    int getX();
    float getZ();
    QVector3D getP();
    QVector3D getN();
    void update();
};

#endif