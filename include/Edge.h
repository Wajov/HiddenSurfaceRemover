#ifndef EDGE_H
#define EDGE_H

#include <algorithm>

#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>

#include "Vertex.h"

class Edge {
private:
    int x, deltaX, y, deltaY;
    float z, dz;
    QVector3D p, dp, n, dn;
    void coordinateToPixel(float coordinateX, float coordinateY, int &pixelX, int &pixelY, int width, int height);

public:
    Edge(Vertex &source, Vertex &target, QMatrix4x4 &MVP, int width, int height);
    ~Edge();
    bool operator <(Edge &edge);
    int getX();
    int getDeltaX();
    int getY();
    int getDeltaY();
    float getZ();
    float getDz();
    QVector3D getP();
    QVector3D getDp();
    QVector3D getN();
    QVector3D getDn();
};

#endif
