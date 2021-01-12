#ifndef SEGMENT_H
#define SEGMENT_H

#include <glm/glm.hpp>

class Segment {
private:
    int x, deltaX;
    float z, dz;
    glm::vec3 p, dp, n, dn;

public:
    Segment(int x, int deltaX, float z, float dz, glm::vec3 &p, glm::vec3 &dp, glm::vec3 &n, glm::vec3 &dn);
    ~Segment();
    int getX();
    int getDeltaX();
    float getZ();
    float getDz();
    glm::vec3 getP();
    glm::vec3 getDp();
    glm::vec3 getN();
    glm::vec3 getDn();
};

#endif