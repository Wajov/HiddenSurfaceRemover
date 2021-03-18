#include "Segment.h"

Segment::Segment(int x, int deltaX, float z, float dz, QVector3D &p, QVector3D &dp, QVector3D &n, QVector3D &dn) {
    this->x = x;
    this->deltaX = deltaX;
    this->z = z;
    this->dz = dz;
    this->p = p;
    this->dp = dp;
    this->n = n;
    this->dn = dn;
}

Segment::~Segment() {}

int Segment::getX() {
    return x;
}

int Segment::getDeltaX() {
    return deltaX;
}

float Segment::getZ() {
    return z;
}

float Segment::getDz() {
    return dz;
}

QVector3D Segment::getP() {
    return p;
}

QVector3D Segment::getDp() {
    return dp;
}

QVector3D Segment::getN() {
    return n;
}

QVector3D Segment::getDn() {
    return dn;
}
