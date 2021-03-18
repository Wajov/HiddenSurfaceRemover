#ifndef SEGMENT_H
#define SEGMENT_H

#include <QVector3D>

class Segment {
private:
    int x, deltaX;
    float z, dz;
    QVector3D p, dp, n, dn;

public:
    Segment(int x, int deltaX, float z, float dz, QVector3D &p, QVector3D &dp, QVector3D &n, QVector3D &dn);
    ~Segment();
    int getX();
    int getDeltaX();
    float getZ();
    float getDz();
    QVector3D getP();
    QVector3D getDp();
    QVector3D getN();
    QVector3D getDn();
};

#endif