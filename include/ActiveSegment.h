#ifndef ACTIVE_SEGMENT_H
#define ACTIVE_SEGMENT_H

#include <glm/glm.hpp>

#include "Segment.h"

class ActiveSegment {
private:
    float z, dz;
    glm::vec3 p, dp, n, dn;

public:
    ActiveSegment();
    ActiveSegment(Segment &segment);
    ~ActiveSegment();
    float getZ();
    glm::vec3 getP();
    glm::vec3 getN();
    void update();
};

#endif