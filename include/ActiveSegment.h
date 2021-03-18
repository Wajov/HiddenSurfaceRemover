#ifndef ACTIVE_SEGMENT_H
#define ACTIVE_SEGMENT_H

#include <QVector3D>

#include "Segment.h"

class ActiveSegment {
private:
    float z, dz;
    QVector3D p, dp, n, dn;

public:
    ActiveSegment();
    ActiveSegment(Segment &segment);
    ~ActiveSegment();
    float getZ();
    QVector3D getP();
    QVector3D getN();
    void update();
};

#endif