#include "Edge.h"

Edge::Edge(Vertex &source, Vertex &target) {
    glm::vec3 p1 = source.getPosition(), p2 = target.getPosition();
    if (p1.y > p2.y)
        std::swap(p1, p2);
    int x1, y1, x2, y2;
    coordinateToPixel(p1.x, p1.y, x1, y1);
    coordinateToPixel(p2.x, p2.y, x2, y2);
    x = x1;
    deltaX = x2 - x1;
    y = y1;
    deltaY = y2 - y1;
    z = p1.z;
    dz = (p2.z - p1.z) / deltaY;
}

Edge::~Edge() {}

void Edge::coordinateToPixel(float coordinateX, float coordinateY, int &pixelX, int &pixelY) {
    int height = 1080, width = 1920;
    float minX = -2.0f, maxX = 2.0f;
    float deltaX = maxX - minX;
    float deltaY = deltaX * height / width;
    float minY = - deltaY / 2, maxY = deltaY / 2;
    pixelX = (int)((coordinateX - minX) / deltaX * width);
    pixelY = (int)((coordinateY - minY) / deltaY * height);
}

bool Edge::operator <(Edge &edge) {
    if (y != edge.y)
        return y < edge.y;
    else if (y + deltaY != edge.y + edge.deltaY)
        return y + deltaY < edge.y + edge.deltaY;
    else if (x != edge.x)
        return x < edge.x;
    else
        return x + deltaX < edge.x + edge.deltaX;
}

int Edge::getX() {
    return x;
}

int Edge::getDeltaX() {
    return deltaX;
}

int Edge::getY() {
    return y;
}

int Edge::getDeltaY() {
    return deltaY;
}

float Edge::getZ() {
    return z;
}

float Edge::getDz() {
    return dz;
}
