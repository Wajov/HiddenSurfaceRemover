#include "Segment.h"

Segment::Segment(int x, int deltaX, float z, float dz, glm::vec3 &p, glm::vec3 &dp, glm::vec3 &n, glm::vec3 &dn) {
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

glm::vec3 Segment::getP() {
    return p;
}

glm::vec3 Segment::getDp() {
    return dp;
}

glm::vec3 Segment::getN() {
    return n;
}

glm::vec3 Segment::getDn() {
    return dn;
}
