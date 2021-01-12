#include "ActiveSegment.h"

ActiveSegment::ActiveSegment() {}

ActiveSegment::ActiveSegment(Segment &segment) {
    z = segment.getZ();
    dz = segment.getDz();
    p = segment.getP();
    dp = segment.getDp();
    n = segment.getN();
    dn = segment.getDn();
}

ActiveSegment::~ActiveSegment() {}

float ActiveSegment::getZ() {
    return z;
}

glm::vec3 ActiveSegment::getP() {
    return p;
}

glm::vec3 ActiveSegment::getN() {
    return n;
}

void ActiveSegment::update() {
    z += dz;
    p += dp;
    n += dn;
}